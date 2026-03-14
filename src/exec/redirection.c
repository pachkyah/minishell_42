#include "minishell.h"

int	execute_heredoc(char *delimiter)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	close(fd[1]); // Close write end so child can read EOF
	return (fd[0]); // Return read end to be dup2'd into STDIN
}


/*
** Loops through the linked list of redirections for a single command.
** It opens files and uses dup2 to move them into STDIN/STDOUT.
*/
int	handle_redirections(t_cmd *cmd)
{
	t_redir	*tmp;
	int		fd;

	tmp = cmd->redirs;
	while (tmp)
	{
		if (tmp->type == REDIR_IN)
			fd = open(tmp->file, O_RDONLY);
		else if (tmp->type == REDIR_OUT)
			fd = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (tmp->type == APPEND)
			fd = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (tmp->type == HEREDOC)
			fd = execute_heredoc(tmp->file);

		if (fd < 0)
		{
			perror(tmp->file);
			return (-1);
		}
		// Apply the FD to the correct stream
		if (tmp->type == REDIR_IN || tmp->type == HEREDOC)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		tmp = tmp->next;
	}
	return (0);
}

void wait_all_children(pid_t last_pid, t_shell *shell)
{
    int status;
    pid_t pid;

    // 1. Wait for the last command specifically to get its exit code
    waitpid(last_pid, &status, 0);
    
    // 2. Extract the exit code using WIFEXITED/WEXITSTATUS macros
    if (WIFEXITED(status))
        shell->exit_status = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        shell->exit_status = 128 + WTERMSIG(status);

    // 3. Clean up all other "zombie" children in the pipeline
    // waitpid with -1 waits for ANY child process
    while ((pid = waitpid(-1, NULL, 0)) > 0) 
        ; 
}

void execute_pipeline(t_cmd *cmd, t_shell *shell)
{
    int     pipefd[2];
    int     prev_fd;
    pid_t   pid;

    prev_fd = 0; // Start with standard input
    while (cmd)
    {
        // 1. Create a pipe if there's a next command
        if (cmd->next)
            pipe(pipefd);

        pid = fork();
        if (pid == 0) // CHILD PROCESS
        {
            // 2. Redirect input from the PREVIOUS pipe
            if (prev_fd != 0)
            {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }
            // 3. Redirect output to the CURRENT pipe
            if (cmd->next)
            {
                close(pipefd[0]); // Close unused read end
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
            }
            
            // 4. Handle files (overwrites pipe redirection if < or > exists)
            handle_redirections(cmd);
            
            // 5. Run the command
            execute_single_command(cmd, shell);
        }
        
        // PARENT PROCESS
        if (prev_fd != 0)
            close(prev_fd);
        if (cmd->next)
        {
            close(pipefd[1]); // Close unused write end
            prev_fd = pipefd[0]; // Save read end for the NEXT command
        }
        cmd = cmd->next;
    }
    // 6. Wait for all children to finish
    wait_all_children();
}