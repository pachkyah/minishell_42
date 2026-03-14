#include "minishell.h"

char	*get_env_path(t_env *env_list)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, "PATH") == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

char	*find_path(char *cmd, t_env *env_list)
{
	char	**paths;
	char	*path_part;
	char	*full_path;
	int		i;

	// 1. If command is already a path, check it directly
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	// 2. Get the PATH string and split it
	paths = ft_split(get_env_path(env_list), ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		// 3. Join path + / + cmd
		path_part = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(path_part, cmd);
		free(path_part);
		// 4. Check if it exists and we can execute it
		if (access(full_path, X_OK) == 0)
		{
			// Clean up the rest of the split and return result
			// (You'll need a free_array helper here)
			return (full_path);
		}
		free(full_path);
		i++;
	}
	// Free the paths array if not found
	return (NULL);
}