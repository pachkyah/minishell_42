#include "minishell.h"

void	execute_command(t_cmd *cmd, t_data *data, int *prev_read_fd)
{
    int		fd[2];
    pid_t	pid;

    // Create a pipe if there is a next command
    if (cmd->next)
    {
        if (pipe(fd) == -1)
            return (perror("pipe"));
    }

    pid = fork();
    if (pid == -1)
        return (perror("fork"));

    if (pid == 0) // CHILD PROCESS
    {
        // Setup input from previous pipe
        if (*prev_read_fd != STDIN_FILENO)
        {
            dup2(*prev_read_fd, STDIN_FILENO);
            close(*prev_read_fd);
        }
        
        // Setup output to current pipe
        if (cmd->next)
        {
            close(fd[0]); // Child doesn't read from its own pipe
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
        }
        
        // Final Step: Execute
        child_process(cmd, data);
    }
    else // PARENT PROCESS
    {
        if (*prev_read_fd != STDIN_FILENO)
            close(*prev_read_fd);
        if (cmd->next)
        {
            close(fd[1]); // Parent doesn't write to the pipe
            *prev_read_fd = fd[0]; // Save read end for the next command
        }
    }
}

void	child_process(t_cmd *cmd, t_data *data)
{
    char	*path;

    // 1. Handle redirections (< > >> <<) here later
    // apply_redirections(cmd);

    // 2. Check if it's a builtin
    if (is_builtin(cmd->args[0]))
    {
        exec_builtin(cmd, data);
        exit(data->last_exit);
    }

    // 3. Find the binary (e.g., /usr/bin/ls)
    path = find_path(cmd->args[0], data->env_list);
    if (!path)
    {
        ft_putstr_fd("Command not found\n", 2);
        exit(127);
    }

    // 4. Transform env_list back to char** and run
    if (execve(path, cmd->args, data->envp) == -1)
    {
        perror("execve");
        exit(1);
    }
}

/* ** Waits for all children to finish and updates the last exit status.
** This happens AFTER the loop so commands run in parallel.
*/
void wait_children(t_data *data)
{
    int	status;
    int	pid;

    while ((pid = wait(&status)) != -1)
    {
        if (WIFEXITED(status))
            data->last_exit = WEXITSTATUS(status);
    }
}

/*
** The main entry point for execution.
*/
void	executor(t_data *data)
{
    t_cmd	*curr;
    int		prev_read_fd;

    curr = data->cmds;
    prev_read_fd = STDIN_FILENO; // The first command reads from the terminal
    
    // 1. Handle Single Builtin (Special case: no fork)
    if (!curr->next && is_builtin(curr->args[0]))
    {
        exec_builtin(curr, data);
        return ;
    }

    // 2. The Pipeline Loop
    while (curr)
    {
        execute_command(curr, data, &prev_read_fd);
        curr = curr->next;
    }

    // 3. Cleanup
    if (prev_read_fd != STDIN_FILENO)
        close(prev_read_fd);
    wait_children(data);
}