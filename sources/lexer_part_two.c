#include "minishell.h"

/**
 * Заполнение вспомогательной структуры
 */
void init_lexer(t_lexer *lexer, char *buffer)
{
	ft_bzero(lexer, sizeof(t_lexer));
	lexer->from = buffer;
	lexer->to = buffer;
	lexer->buffer = buffer;
}

/**
 * Обновляет value накопившейся подстрокой от from до to,
 * обновляет quote,
 * инкремент buffer,
 * from и to заполняет новым buffer.
 */
void update_lexer(t_lexer *lexer, char quote)
{
	lexer->value = join_and_free_srcs(lexer->value,
									  ft_substr(lexer->from,
												0, lexer->to - lexer->from));
	lexer->quote = quote;
	lexer->buffer++;
	lexer->from = lexer->buffer;
	lexer->to = lexer->buffer;
}

/**
 * Добавляет к value значение переменной,
 * инкремент buffer чтобы пропустить имя переменной.
 * TODO ПОМЕЯТЬ НА НОРМАЛЬНЫЙ ОТДЕЛЬНОЙ ЗАДАЧЕЙ
 */
void add_env(t_lexer *lexer)
{
	lexer->buffer++;
	lexer->value = join_and_free_srcs(lexer->value, ft_strdup("ENV_VALUE"));
	while (*lexer->buffer && is_valid_char_for_env_var_name(*lexer->buffer))
		lexer->buffer++;
}

/**
 * Открывающая кавычка " или '
 */
int handle_open_quotes(t_lexer *lexer)
{
	if (!lexer->quote && ft_strchr(QUOTES, *lexer->buffer))
	{
		update_lexer(lexer, *lexer->buffer);
		return NOT_SKIP;
	}
	else
		return SKIP;
}

/**
 * Закрывающая кавычка " или '
 */
int handle_close_quotes(t_lexer *lexer)
{
	if (lexer->quote && *lexer->buffer == lexer->quote)
	{
		update_lexer(lexer, 0);
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
		&& (is_valid_char_for_env_var_name(*lexer->buffer)))
	{
		update_lexer(lexer, lexer->quote);
		add_env(lexer);
		lexer->from = lexer->buffer;
		lexer->to = lexer->buffer;
		return NOT_SKIP;
	}
	else
		return SKIP;
}

int handle_simple_char(t_lexer *lexer)
{
	lexer->buffer++;
	lexer->to = lexer->buffer;
	if (!*lexer->buffer ||
		(ft_isspace(*lexer->buffer) && !lexer->quote))
	{
		update_lexer(lexer, 0);
		lexer->buffer--;
		lexer->from--;
		lexer->to--;
	}
	return NOT_SKIP;
}

/**
 * Откусывает от буфера один токен.
 */
t_token *get_new_token(char **buffer)
{
	t_lexer lexer;
	int (*p[4])(t_lexer *lexer);
	size_t i;

	init_lexer(&lexer, *buffer);
	p[0] = handle_open_quotes;
	p[1] = handle_close_quotes;
	p[2] = handle_env_char;
	p[3] = handle_simple_char;
	while (*lexer.buffer && (lexer.quote || !ft_isspace(*lexer.buffer)))
	{
		i = 0;
		while (p[i](&lexer) == SKIP && i < 4)
			i++;
	}
	*buffer = lexer.buffer;
	return new_token(lexer.value);
}
