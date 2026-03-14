#include "minishell.h"

/*
** Closes the pipe file descriptors in the parent process.
** This is crucial to send EOF to the next command in the pipeline.
*/
void	close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

/*
** A helper to handle the duplication logic for pipes.
** prev_read_fd: The read-end of the pipe from the PREVIOUS command.
** fd: The current pipe for the NEXT command.
*/
void	handle_pipe_dups(t_cmd *cmd, int prev_read_fd, int *fd)
{
	// If not the first command, take input from previous pipe
	if (prev_read_fd != STDIN_FILENO)
	{
		dup2(prev_read_fd, STDIN_FILENO);
		close(prev_read_fd);
	}
	// If not the last command, send output to current pipe
	if (cmd->next)
	{
		close(fd[0]); // Child doesn't read from its own pipe
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
}