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
char *lexer(char *buffer)
{
	t_base base;

	ft_bzero(&base, sizeof(t_base));
	base.buffer = buffer;
	while (base.buffer[base.i])
	{
		while (ft_isspace(base.buffer[base.i]))
			base.i++;
		if (base.buffer[base.i])
			push_token_back(&(base.tokens), get_new_token(&base));
	}

	print_all_tokens(base.tokens);
	free_list_of_tokens(base.tokens);
	return base.buffer;
}
