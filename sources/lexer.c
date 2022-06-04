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
 * TODO узнать подробнее какие бывают ограничения на имена переменных
 * для bash shell
 */
int is_valid_char_for_env_var_name(char env_var_name_char)
{
	return ft_isalpha(env_var_name_char) || ft_isdigit(env_var_name_char) || env_var_name_char == '_';
}

char *join_and_free_srcs(char *s1, char *s2)
{
	char *result;

	if (!s1)
		result = s2;
	else if (!s2)
		result = s1;
	else
	{
		result = ft_strjoin(s1, s2);
		free(s1);
		free(s2);
	}
	return result;
}

/**
 * Разделяет буфер на токены
 */
t_token *lexer(char *buffer)
{
	t_lexer lexer;
	int (*p[5])(t_lexer *lexer);
	size_t i;

	lexer_init(&lexer, buffer);
	p[0] = handle_quotes;
	p[1] = handle_env_char;
	p[2] = handle_redirect;
	p[3] = handle_spaces;
	p[4] = handle_simple_char;
	while (*lexer.buffer && ft_isspace(*lexer.buffer))
		lexer.buffer++;
	lexer.from = lexer.buffer;
	while (*lexer.buffer)
	{
		i = 0;
		while (p[i](&lexer) == SKIP && i < 5)
			i++;
	}
	if (lexer.value)
		lexer_add_token(&lexer);
	return lexer.tokens;
}
