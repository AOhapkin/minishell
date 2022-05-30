#include "minishell.h"

/**
 * Заполнение вспомогательной структуры
 */
void init_lexer(t_lexer *lexer, size_t current_index, char quote, char *value)
{
	ft_bzero(lexer, sizeof(t_lexer));
	lexer->from = current_index;
	lexer->to = current_index;
	lexer->quote = quote;
	lexer->value = value;
}

char *join_value_and_free_srcs(t_base *base, t_lexer *lexer)
{
	return join_and_free_srcs(lexer->value,
						ft_substr(base->buffer + lexer->from,
										0, lexer->to - lexer->from));
}

/**
 * Открывающая кавычка " или '
 */
int handle_open_quotes(t_base *base, t_lexer *lexer)
{
	if (!lexer->quote && ft_strchr(QUOTES, base->buffer[base->i]))
	{
		lexer->value = join_value_and_free_srcs(base, lexer);
		init_lexer(lexer, base->i + 1, base->buffer[base->i], lexer->value);
		base->i++;
		return NOT_FINAL;
	}
	else
		return SKIP;
}

/**
 * Закрывающая кавычка " или '
 */
int handle_close_quotes(t_base *base, t_lexer *lexer)
{
	if (lexer->quote && base->buffer[base->i] == lexer->quote)
	{
		lexer->value = join_value_and_free_srcs(base, lexer);
		base->i++;
		init_lexer(lexer, base->i, 0, lexer->value);
		if (!(base->buffer[base->i] && !ft_isspace(base->buffer[base->i])))
			return FINAL;
		return NOT_FINAL;
	}
	else
		return SKIP;
}

/**
 * Обработка символа $
 */
int handle_env_char(t_base *base, t_lexer *lexer)
{
	if (base->buffer[base->i] == ENV_CHAR
		&& (!lexer->quote || lexer->quote == DOUBLE_QUOTE)
		&& (is_valid_char_for_env_var_name(base->buffer[base->i + 1])
			|| ft_strchr(QUOTES, base->buffer[base->i])))
	{
		lexer->value = join_value_and_free_srcs(base, lexer);
		base->i++;


		lexer->value = join_and_free_srcs(lexer->value, ft_strdup("ENV_VALUE"));


		while (base->buffer[base->i] && is_valid_char_for_env_var_name(base->buffer[base->i]))
			base->i++;
		if (!(base->buffer[base->i] && !ft_isspace(base->buffer[base->i])))
			return FINAL;
		init_lexer(lexer, base->i, lexer->quote, lexer->value);
		return NOT_FINAL;
	}
	else
		return SKIP;
}

int handle_simple_char(t_base *base, t_lexer *lexer)
{
	base->i++;
	lexer->to = base->i;
	if (!(base->buffer[base->i]) || (ft_isspace(base->buffer[base->i]) && !lexer->quote))
	{
		lexer->value = join_value_and_free_srcs(base, lexer);
		return FINAL;
	}
	return NOT_FINAL;
}

/**
 * Откусывает от буфера один токен.
 */
t_token *get_new_token(t_base *base)
{
	t_lexer lexer;
	int (*p[4]) (t_base *base, t_lexer *lexer);
	size_t i;

	init_lexer(&lexer, base->i, 0, NULL);
	p[0] = handle_open_quotes;
	p[1] = handle_close_quotes;
	p[2] = handle_env_char;
	p[3] = handle_simple_char;
	while (base->buffer[base->i]
	&& (!ft_isspace(base->buffer[base->i]) || lexer.quote))
	{
		i = 0;
		while (p[i](base, &lexer) == SKIP && i < 4)
			i++;
	}
	return new_token(lexer.value);
}
