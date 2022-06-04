#include "minishell.h"

/**
 * Обработка кавычек " или '
 */
int handle_quotes(t_lexer *lexer)
{
	if ((!lexer->quote && ft_strchr(QUOTES, *lexer->buffer))
		|| lexer->quote && *lexer->buffer == lexer->quote)
	{
		if (lexer->quote && *lexer->buffer == lexer->quote)
			lexer_update_value_and_quote(lexer, 0);
		else
			lexer_update_value_and_quote(lexer, *lexer->buffer);
		lexer->buffer++;
		lexer->from = lexer->buffer;
		return NOT_SKIP;
	}
	else
		return SKIP;
}

/**
 * Обработка символа $
 */
int handle_env_char(t_lexer *lexer)
{
	if (*lexer->buffer == ENV_CHAR
		&& (!lexer->quote || lexer->quote == DOUBLE_QUOTE)
		&& (is_valid_char_for_env_var_name(lexer->buffer[1])))
	{
		lexer_update_value_and_quote(lexer, lexer->quote);
		lexer_add_env_to_value_and_skip_name(lexer);
		return NOT_SKIP;
	}
	else
		return SKIP;
}

/**
 * Обработка символов перенаправления ввода/вывода
 */
int handle_redirect(t_lexer *lexer)
{
	if (ft_strchr(REDIRECTIONS_CHARS, *lexer->buffer)
		&& !lexer->quote)
	{
		lexer_add_token(lexer);
		if (!ft_strncmp(lexer->buffer, "<<", 2) || !ft_strncmp(lexer->buffer, ">>", 2))
			lexer->buffer += 2;
		else
			lexer->buffer += 1;
		lexer_add_token(lexer);
		return NOT_SKIP;
	}
	else
		return SKIP;
}

/**
 * Пробельные символы,
 * создать токен из накопившегося и пропускает пробелы
 */
int handle_spaces(t_lexer *lexer)
{
	if (ft_isspace(*lexer->buffer) && !lexer->quote)
	{
		lexer_add_token(lexer);
		while (lexer->buffer && ft_isspace(*lexer->buffer))
			lexer->buffer++;
		lexer->from = lexer->buffer;
		return NOT_SKIP;
	}
	return SKIP;
}

/**
 * Обычный символ,
 * пропустить 1 символ и если следующего нет создать токен из остатков
 */
int handle_simple_char(t_lexer *lexer)
{
	lexer->buffer++;
	if (!*lexer->buffer)
	{
		lexer_add_token(lexer);
		lexer->from = lexer->buffer;
	}
	return NOT_SKIP;
}
