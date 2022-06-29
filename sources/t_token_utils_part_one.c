#include "minishell.h"

t_token	*new_token(char *value)
{
	t_token	*new;

	new = ft_memalloc(sizeof(t_token));
	if (new)
		new->value = value;
	return (new);
}

int	get_size(t_token *head)
{
	int	len;

	len = 0;
	while (head != NULL)
	{
		head = head->next;
		len++;
	}
	return (len);
}

void	free_list_of_tokens(t_token *head)
{
	t_token	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}

t_token	*get_last_token(t_token *head)
{
	while (head->next)
		head = head->next;
	return (head);
}
