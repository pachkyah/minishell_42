#include "minishell.h"

// Находит значение переменной в вашем списке окружения
char	*get_env_value(char *var_name, t_shell *shell)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(var_name);
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(shell->last_status)); // Обработка $? 
	while (shell->env && shell->env[i])
	{
		if (ft_strncmp(shell->env[i], var_name, len) == 0 
			&& shell->env[i][len] == '=')
			return (ft_strdup(shell->env[i] + len + 1));
		i++;
	}
	return (ft_strdup("")); // Если переменная не найдена, она заменяется на пустоту
}

// Основная логика: ищет $ и заменяет имя на значение
char	*expand_variables(char *input, t_shell *shell)
{
	char	*result;
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	// Здесь должна быть логика прохода по строке, 
	// которая при встрече '$' вызывает get_env_value.
	// ВАЖНО: Пропускай всё, если quote == '\''[cite: 109].
	
	// (Для краткости: тут мы выделяем новую строку и склеиваем части)
	return (result);
}
