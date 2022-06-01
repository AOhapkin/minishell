#include "minishell.h"

/**
 * Заполнение вспомогательной структуры
 */
void lexer_init(t_lexer *lexer, char *buffer)
{
	ft_bzero(lexer, sizeof(t_lexer));
	lexer->from = buffer;
	lexer->buffer = buffer;
}

/**
 * Обновляет value накопившейся подстрокой от from до buffer (*buffer не войдет),
 * обновляет quote и from.
 */
void lexer_update_value_and_quote(t_lexer *lexer, char quote)
{
	if (!(lexer->buffer == lexer->from && !lexer->quote))
		lexer->value = join_and_free_srcs(lexer->value,
										  ft_substr(lexer->from,
													0, lexer->buffer - lexer->from));
	lexer->quote = quote;
	lexer->from = lexer->buffer;
}

/**
 * Скидывает накопившееся между from и buffer в value,ё
 * из value делает токен и кладет его в конец списка.
 */
void lexer_add_token(t_lexer *lexer)
{
	lexer_update_value_and_quote(lexer, 0);
	if (lexer->value)
		push_token_back(&(lexer->tokens), new_token(lexer->value));
	lexer->value = NULL;
}

/**
 * Добавляет к value значение переменной,
 * инкремент buffer чтобы пропустить имя переменной.
 * TODO ПОМЕЯТЬ НА НОРМАЛЬНЫЙ ОТДЕЛЬНОЙ ЗАДАЧЕЙ
 */
void lexer_add_env_to_value_and_skip_name(t_lexer *lexer)
{
	lexer->buffer++;
	lexer->value = join_and_free_srcs(lexer->value, ft_strdup("ENV_VALUE"));
	while (*lexer->buffer && is_valid_char_for_env_var_name(*lexer->buffer))
		lexer->buffer++;
	lexer->from = lexer->buffer;
}
