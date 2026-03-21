/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamelina <kamelina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 20:07:21 by kamelina          #+#    #+#             */
/*   Updated: 2026/03/14 20:08:07 by kamelina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*line;
	t_shell	shell;

	(void)argc; (void)argv;
	shell.env = envp;
	shell.last_status = 0;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		
		if (*line)
			add_history(line);
		
		free(line);
	}
	return (0);
}