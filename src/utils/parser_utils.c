#include "minishell.h"

/* ** Создает новый узел (токен). 
** Мы выделяем память под структуру и записываем туда значение и тип.
*/
t_token	*ft_new_token(char *value, t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = value;
	new->type = type;
	new->next = NULL;
	return (new);
}

/* ** Добавляет созданный токен в конец связного списка. 
** Это важно для сохранения порядка команд (например: ls | grep).
*/
void	ft_token_add_back(t_token **head, t_token *new)
{
	t_token	*tmp;

	if (!head || !new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

/* ** Очищает весь список токенов и освобождает память.
** Обязательно по сабжекту (Memory leaks will not be tolerated).
*/
void	free_tokens(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->value)
			free(head->value);
		free(head);
		head = tmp;
	}
}
