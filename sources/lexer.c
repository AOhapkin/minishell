#include "minishell.h"

void init_lexer(t_lexer *lexer, char *current, char quote)
{
	ft_bzero(lexer, sizeof(t_lexer));
	lexer->start = current;
	lexer->finish = current;
	lexer->quote = quote;
}

/**
 * Делит входной буфер на "токены"
 */
t_token *get_new_token(char **buffer)
{
	char *value;
	char *current;
	t_lexer lexer;


	value = NULL;
	current = *buffer;

	init_lexer(&lexer, current, 0);
	while (*current && !ft_isspace(*current))
	{
		// открывающая кавычка " или '
		if (!lexer.quote && ft_strchr(QUOTES, *current)
			&& ft_strchr(current + 1, *current))
		{
			value = join_and_free_srcs(value, ft_substr(lexer.start, 0, lexer.finish - lexer.start));
			init_lexer(&lexer, current + 1, *current);
			current++;
		}
		// закрывающая кавычка " или '
		else if (lexer.quote && *current == lexer.quote)
		{
			value = join_and_free_srcs(value, ft_substr(lexer.start, 0, lexer.finish - lexer.start));
			current++;
			if (!(*current && !ft_isspace(*current)))
				break;;
			init_lexer(&lexer, current, 0);
		}
		// переменная `$env`
		else if (*current == ENV_CHAR
			&& (!lexer.quote || lexer.quote == DOUBLE_QUOTE)
			&& (is_valid_char_for_env_var_name(*(current + 1))
				|| ft_strchr(QUOTES, *(current + 1))))
		{
			value = join_and_free_srcs(value, ft_substr(lexer.start, 0, lexer.finish - lexer.start));
			current++;

			// todo заглушка для добавления переменной
			value = join_and_free_srcs(value, ft_strdup("ENV_VALUE"));
			while (*current && is_valid_char_for_env_var_name(*current))
				current++;
			if (!(*current && !ft_isspace(*current)))
				break;;
			init_lexer(&lexer, current, lexer.quote);
		}
		// остальные случаи
		else
		{
			current++;
			if (!(*current && !ft_isspace(*current)))
			{
				value = join_and_free_srcs(value, ft_substr(lexer.start, 0, lexer.finish - lexer.start + 1));
				break;
			}
			lexer.finish = current;
		}
	}
	*buffer = current;
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
		if (*buffer)
			push_token_back(&first_token, get_new_token(&buffer));
	}


	while (first_token)
	{
		printf("minishell > %s\n", first_token->value);
		first_token = first_token->next;
	}


	return 1;
}
