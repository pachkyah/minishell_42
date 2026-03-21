/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envir_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ypachkou <ypachkou@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 18:58:28 by ypachkou          #+#    #+#             */
/*   Updated: 2026/03/21 18:58:37 by ypachkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *env_new(char *key, char *value)
{
    t_env *node = malloc(sizeof(t_env));
    if (!node)
        return NULL;
    node->key = ft_strdup(key);
    node->value = ft_strdup(value);
    node->next = NULL;
    return node;
}

void env_add_back(t_env **env, t_env *new)
{
    t_env *tmp;

    if (!*env)
    {
        *env = new;
        return;
    }
    tmp = *env;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

t_env *env_init(char **envp)
{
    t_env *env = NULL;
    int i = 0;

    while (envp[i])
    {
        char *equal = ft_strchr(envp[i], '=');
        if (equal)
        {
            char *key = ft_substr(envp[i], 0, equal - envp[i]);
            char *value = ft_strdup(equal + 1);
            env_add_back(&env, env_new(key, value));
            free(key);
            free(value);
        }
        i++;
    }
    return env;
}