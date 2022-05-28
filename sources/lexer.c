#include "minishell.h"

/**
 * Парсит конец токена который начинается с кавычки.
 */
char *parse_quot_first(t_token *token, char *buffer)
{
	char quote_char;

	quote_char = *buffer;
	if (!*buffer && quote_char != DOUBLE_QUOTE && quote_char != SINGLE_QUOTE)
		exit(1);
	buffer++;
	// до следующей кавычки или конца буфера
	while (*buffer && *buffer != quote_char)
		buffer++;
	token->last_char = buffer;
	if (*buffer)
		buffer++;
	return buffer;
}

/**
 * Парсит конец токена который не начинается с кавычки.
 */
char *parse_no_quote_first(t_token *token, char *buffer)
{
	if (!*buffer && *buffer == DOUBLE_QUOTE && *buffer == SINGLE_QUOTE)
		exit(1);
	// до пробела кавычки или конца буфера
	while (*buffer && !ft_isspace(*buffer) && !ft_strchr(QUOTES, *buffer))
	{
		token->last_char = buffer;
		buffer++;
	}
	if (!*buffer)
		token->last_char = buffer;
	return buffer;
}

/**
 * Делит входной буфер на "слова".
 */
t_token *get_new_token(char **buffer)
{
	t_token *token;

	token = new_token(*buffer);
	while (**buffer && !ft_isspace(**buffer))
	{
		if (ft_strchr(QUOTES, **buffer))
			*buffer = parse_quot_first(token, *buffer);
		else
			*buffer = parse_no_quote_first(token, *buffer);
	}
	return token;
}

/**
 * Принимает строку из prompt
 * и делит ее на лексемы.
 */
int lexer(char *buffer)
{
	t_token *first_token;
	t_token *new_token;

	first_token = NULL;
	while (*buffer)
	{
		while (ft_isspace(*buffer))
			buffer++;
		new_token = get_new_token(&buffer);
		push_token_back(&first_token, new_token);
	}
	return 1;
}
