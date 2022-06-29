#include "minishell.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}

/**
 * Заполнение вспомогательной структуры
 */
void	lexer_init(t_lexer *lexer, char *buffer)
{
	ft_bzero(lexer, sizeof(t_lexer));
	lexer->from = buffer;
	lexer->buffer = buffer;
}

/**
 * Обновляет value накопившейся подстрокой от from до buffer (*buffer не войдет),
 * обновляет quote и from.
 */
void	lexer_update_value_and_quote(t_lexer *lexer, char quote)
{
	if (!(lexer->buffer == lexer->from && !lexer->quote))
		lexer->value = join_and_free_srcs(lexer->value,
				ft_substr(lexer->from,
					0, lexer->buffer - lexer->from));
	lexer->quote = quote;
	lexer->from = lexer->buffer;
}

/**
 * Скидывает накопившееся между from и buffer в value,
 * из value делает токен и кладет его в конец списка.
 */
t_token	*lexer_add_token(t_lexer *lexer)
{
	t_token	*new;

	new = NULL;
	lexer_update_value_and_quote(lexer, 0);
	if (lexer->value)
	{
		new = new_token(lexer->value);
		push_token_back(&(lexer->tokens), new);
	}
	lexer->value = NULL;
	return (new);
}

char	*get_env_name(char *buffer)
{
	char	*from;
	char	*to;
	char	*name;

	if (buffer)
	{
		from = buffer;
		to = from;
		while (*to && is_valid_char_for_env_var_name(*to))
			to++;
		name = ft_memalloc(to - from + 1);
		return (ft_strncpy(name, from, to - from));
	}
	return (NULL);
}

/**
 * Добавляет к value значение переменной,
 * инкремент buffer чтобы пропустить имя переменной.
 */
void	lexer_add_env_to_value_and_skip_name(t_lexer *lexer)
{
	char	*env_name;
	t_list	*env_list;

	lexer->buffer++;
	if (*(lexer->buffer) == '?')
	{
		env_name = ft_strdup("?");
		lexer->value = join_and_free_srcs(lexer->value, ft_itoa(g_singleton->last_exit_stat));
	}
	else
	{
		env_name = get_env_name(lexer->buffer);
		env_list = find_element_by_key(g_singleton->env, env_name);
		if (env_list
			&& ((t_env*)(env_list->content))->value
			&& ft_strlen(((t_env*)(env_list->content))->value) > 0)
			lexer->value = join_and_free_srcs(lexer->value, ft_strdup(((t_env *)(env_list->content))->value));
	}
	lexer->buffer = lexer->buffer + ft_strlen(env_name);
	free(env_name);
	lexer->from = lexer->buffer;
}
