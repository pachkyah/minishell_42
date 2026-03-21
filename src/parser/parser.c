#include "minishell.h"

/* Определяет длину обычного слова, учитывая кавычки.
** Кавычки «прячут» спецсимволы внутри себя. */
static int	get_token_len(char *line)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '\"') && !quote)
			quote = line[i];
		else if (line[i] == quote)
			quote = 0;
		else if (!quote && (line[i] == ' ' || line[i] == '|' || 
				 line[i] == '<' || line[i] == '>'))
			break ;
		i++;
	}
	return (i);
}

/* Определяет длину спецсимволов для редиректов и пайпов. */
static int	get_special_len(char *line)
{
	if ((line[0] == '>' && line[1] == '>') || 
		(line[0] == '<' && line[1] == '<'))
		return (2);
	return (1);
}

/* Выделяет память и копирует значение токена[cite: 25]. */
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

/* Определяет тип токена для упрощения работы Person A[cite: 94]. */
static t_token_type	get_token_type(char *val)
{
	if (val[0] == '|')
		return (TOKEN_PIPE);
	if (val[0] == '<' || val[0] == '>')
		return (TOKEN_REDIR);
	return (TOKEN_WORD);
}

/* Главная функция лексера: разбивает строку на список токенов. */
t_token	*tokenize(char *line)
{
	t_token	*head;
	int		len;
	char	*val;

	head = NULL;
	while (*line)
	{
		while (*line == ' ' || (*line >= 9 && *line <= 13))
			line++;
		if (!*line)
			break ;
		if (*line == '|' || *line == '<' || *line == '>')
			len = get_special_len(line);
		else
			len = get_token_len(line);
		val = copy_token_val(line, len);
		if (!val)
			return (NULL); // В идеале тут должна быть функция очистки всего списка
		ft_token_add_back(&head, ft_new_token(val, get_token_type(val)));
		line += len;
	}
	return (head);
}
