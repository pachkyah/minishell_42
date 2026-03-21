#include "minishell.h"

// Вспомогательная функция для склейки пути
static char	*join_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*full_path;
	int		i;

	i = 0;
	// Ищем строку PATH= в окружении
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	// Режем пути по двоеточию
	paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		full_path = join_path(paths[i], cmd);
		if (access(full_path, X_OK) == 0)
		{
			// Тут надо бы очистить массив paths перед возвратом
			return (full_path);
		}
		free(full_path);
	}
	// Очистка массива paths
	return (NULL);
}
