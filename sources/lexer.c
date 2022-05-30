#include "minishell.h"

/**
 * Печатает токены
 */
void print_all_tokens(t_token *token)
{
	t_token *current = token;
	while (current)
	{
		printf("|%s|\n", current->value);
		current = current->next;
	}
}

/**
 * Принимает строку из prompt
 * делит ее на токены и печатает.
 */
char *lexer(char *buffer)
{
	t_token *tokens;

	tokens = NULL;
	while (*buffer)
	{
		while (ft_isspace(*buffer))
			buffer++;
		if (*buffer)
			push_token_back(&tokens, get_new_token(&buffer));
	}

	print_all_tokens(tokens);
	free_list_of_tokens(tokens);
	return NULL;
}
