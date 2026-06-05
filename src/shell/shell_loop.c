/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypachkou <ypachkou@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:23:18 by ypachkou          #+#    #+#             */
/*   Updated: 2026/06/05 17:24:17 by ypachkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_line(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;

	if (*line)
		add_history(line);

	tokens = tokenize(line);
	if (!tokens)
		return ;

	if (!syntax_check(tokens))
	{
		free_tokens(tokens);
		return ;
	}

	cmds = parse_tokens(tokens);
	if (!cmds)
	{
		free_tokens(tokens);
		return ;
	}

	shell->last_status = execute_commands(cmds, shell);

	free_tokens(tokens);
	free_cmds(cmds);
}

void	shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;

		process_line(line, shell);

		free(line);
	}
}