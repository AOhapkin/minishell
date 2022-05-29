#include "minishell.h"

/**
 * Печатает токены
 */
void print_all_tokens(t_token *token)
{
	t_token *current = token;
	while (current)
	{
		printf("%s\n", current->value);
		current = current->next;
	}
}

/**
 * Принимает строку из prompt
 * делит ее на токены и печатает.
 */
int lexer(char *buffer)
{
	t_token *first_token;

	first_token = NULL;
	while (*buffer)
	{
		while (ft_isspace(*buffer))
			buffer++;
		if (*buffer)
			push_token_back(&first_token, get_new_token(&buffer));
	}

	print_all_tokens(first_token);
	free_list_of_tokens(first_token);
	return 1;
}
