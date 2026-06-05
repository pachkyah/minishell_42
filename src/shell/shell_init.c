/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypachkou <ypachkou@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:25:26 by ypachkou          #+#    #+#             */
/*   Updated: 2026/06/05 17:27:05 by ypachkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_init(t_shell *shell, char **envp)
{
	if (!shell)
		return (ERROR);

	shell->env = env_init(envp);
	if (!shell->env)
		return (ERROR);

	shell->last_status = 0;

	init_signals();

	return (SUCCESS);
}