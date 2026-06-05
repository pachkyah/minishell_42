/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypachkou <ypachkou@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 20:07:21 by kamelina          #+#    #+#             */
/*   Updated: 2026/06/05 17:26:29 by ypachkou         ###   ########.fr       */
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
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;

	shell_init(&shell, envp);
	shell_loop(&shell);
	shell_destroy(&shell);

	return (0);
}


// int main(int argc, char **argv, char **envp)
// {
// 	char	*line;
// 	t_shell	shell;
// 	t_token	*tokens;
// 	t_cmd	*cmds;

// 	(void)argc;
// 	(void)argv;

// 	shell.env = env_init(envp);
// 	shell.last_status = 0;

// 	init_signals();

// 	while (1)
// 	{
// 		line = readline("minishell> ");
// 		if (!line)
// 		{
// 			printf("exit\n");
// 			break ;
// 		}
		
// 		if (*line)
// 			add_history(line);

// 		tokens = tokenize(line);
// 		if (!tokens)
// 		{
// 			free(line);
// 			continue ;
// 		}

// 		if (!syntax_check(tokens))
// 		{
// 			free_tokens(tokens);
// 			free(line);
// 			continue ;
// 		}

// 		cmds = parse_tokens(tokens);
// 		if (!cmds)
// 		{
// 			free_tokens(tokens);
// 			free(line);
// 			continue ;
// 		}

// 		shell.last_status = execute_commands(cmds, &shell);

// 		free_tokens(tokens);
// 		free_cmds(cmds);
// 		free(line);
// 	}

// 	free_env(shell.env);
// 	rl_clear_history();
// 	return (0);
// }
