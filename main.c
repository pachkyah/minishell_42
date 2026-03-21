/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypachkou <ypachkou@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 20:07:21 by kamelina          #+#    #+#             */
/*   Updated: 2026/03/21 19:00:08 by ypachkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Entry point of the minishell program.
 *
 * Initializes the shell structure and enters an interactive loop
 * that continuously reads user input using the readline library.
 * Non-empty input lines are added to the command history.
 *
 * The loop terminates when readline returns NULL (e.g., on EOF
 * or when the user presses Ctrl+D).
 *
 * @param argc Argument count (unused).
 * @param argv Argument vector (unused).
 * @param envp Environment variables passed to the shell.
 *
 * @return int Returns 0 upon normal termination.
 */
int main(int argc, char **argv, char **envp)
{
	char	*line;
	t_shell	shell;

	// (void)argc; (void)argv;
	// shell.env = envp;
	// shell.last_status = 0;

    shell.env = env_init(envp);

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		
		if (*line)
			add_history(line);
		
		t_token *tokens = tokenize(line);
        t_cmd *cmds = parse_tokens(tokens);

        execute_commands(cmds, &shell);

        free_tokens(tokens);
        free_cmds(cmds);
        free(line);
	}
	return (0);
}