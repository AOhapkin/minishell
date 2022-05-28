#include "minishell.h"

t_token *new_token(char *first_char)
{
	t_token *new;

	new = ft_memalloc(sizeof(t_token));
	if (new)
	{
		new->first_char = first_char;
		new->last_char = first_char;
		new->next = NULL;
		return (new);
	}
//	return (NULL);
	perror("memalloc problem");
	exit(1);
}

int get_size(t_token *head)
{
	int len;

	len = 0;
	while (head != NULL)
	{
		head = head->next;
		len++;
	}
	return (len);
}

void free_list_of_tokens(t_token *head)
{
	t_token *temp;

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