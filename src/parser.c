#include "minishell.h"

static int	calculate_len(char *line)
{
	if (*line == '|' || *line == '<' || *line == '>')
		return (get_special_len(line));
	return (get_token_len(line));
}

static char	*copy_token_val(char *line, int len)
{
	char	*val;
	int		i;

	val = malloc(sizeof(char) * (len + 1));
	if (!val)
		return (NULL);
	i = 0;
	while (i < len)
	{
		val[i] = line[i];
		i++;
	}
	val[len] = '\0';
	return (val);
}

t_token	*tokenize(char *line)
{
	t_token	*head;
	int		len;
	char	*val;

	head = NULL;
	while (*line)
	{
		while (*line == ' ')
			line++;
		if (!*line)
			break ;
		len = calculate_len(line);
		val = copy_token_val(line, len);
		if (!val)
			return (NULL); //очистка
		ft_token_add_back(&head, ft_new_token(val, get_token_type(*line)));
		line += len;
	}
	return (head);
}