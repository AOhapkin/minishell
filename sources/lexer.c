#include "minishell.h"

/**
 * Делит входной буфер на "токены"
 */
t_token *get_new_token(char **buffer)
{
	char *value;

	value = NULL;
	while (**buffer && !ft_isspace(**buffer))
	{
		if (ft_strchr(QUOTES, **buffer))
			*buffer = parse_lexeme_with_quote(&value, *buffer);
		else
			*buffer = parse_lexeme_without_quote(&value, *buffer);
	}
	return new_token(value);
}

/**
 * Принимает строку из prompt
 * и делит ее на лексемы.
 */
int lexer(char *buffer)
{
	t_token *first_token;

	first_token = NULL;
	while (*buffer)
	{
		while (ft_isspace(*buffer))
			buffer++;
		push_token_back(&first_token, get_new_token(&buffer));
	}
	printf("%s\n", first_token->value);
	return 1;
}
