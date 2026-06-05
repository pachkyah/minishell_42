/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypachkou <ypachkou@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:25:20 by ypachkou          #+#    #+#             */
/*   Updated: 2026/06/05 17:27:35 by ypachkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;

		free(env->key);
		free(env->value);
		free(env);

		env = tmp;
	}
}

void	shell_cleanup(t_shell *shell)
{
	if (!shell)
		return ;

	free_env(shell->env);

	rl_clear_history();
}