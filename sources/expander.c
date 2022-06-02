#include "minishell.h"

int is_redirection_operator(t_token *token)
{
	return !strcmp(token->value, ">>")
			|| !strcmp(token->value, ">")
			|| !strcmp(token->value, "<<")
			|| !strcmp(token->value, "<");
}

t_token *handle_redirection_tokens(t_base *base, t_token *token)
{
	while (token && is_redirection_operator(token))
	{
		if (!strcmp(token->value, ">"))
		{
			token->type = REDIRECT_OUTPUT;
			base->output = token;
		}
		else if (!strcmp(token->value, ">>"))
		{
			token->type = APPENDING_REDIRECTED_OUTPUT;
			base->output = token;
		}
		else if (!strcmp(token->value, "<"))
		{
			token->type = REDIRECT_INPUT;
			base->input = token;
		}
		else if (!strcmp(token->value, "<<"))
		{
			token->type = HERE_DOCUMENTS;
			base->input = token;
		}

		token = token->next;
		if (!token || is_redirection_operator(token) || !strcmp(token->value, "|"))
		{
			printf("minishell : syntax error near unexpected token `%s'\n", token->value ? token->value : "newline");
			return NULL;
		}
		else
		{
			token->type = REDIRECT_ARG_TYPE;
			token = token->next;
		}
	}
	return token;
}

t_token *handle_command_token(t_base *base, t_token *token)
{
	token = handle_redirection_tokens(base, token);
	if (token && !strcmp(token->value, "echo"))
		token->type = ECHO_TYPE;
	else if (token && ft_strchr(base->command->value, '/'))
	{
		token->type = EXEC_TYPE;
		/*
		 * TODO можно тут же устроить валидацию
		 * 1. файл/или директория
		 * 2. права доступа
		 * No such file or directory
		 * Permission denied
		 */
	}
	else
	{
		printf("minishell : %s command not found\n", token->value ? token->value : "newline");
		return NULL;
	}
	base->command = token;
	return token->next;
}

t_token *handle_flag_tokens(t_base *base, t_token *token)
{
	while (token && !base->contain_args && base->command->type == ECHO_TYPE)
	{
		token = handle_redirection_tokens(base, token);
		if (token && !strcmp(token->value, "-n"))
		{
			token->type = ECHO_N_FLAG;
			base->contain_flag = TRUE;
			token = token->next;
		}
		else
			break;
	}
	return token;
}

t_token *handle_argument_tokens(t_base *base, t_token *token)
{
	while (token && strcmp(token->value, "|"))
	{
		token = handle_redirection_tokens(base, token);
		if (token)
		{
			token->type = COMMAND_ARG_TYPE;
			base->contain_args = TRUE;
			token = token->next;
		}
		else
			break;
	}
	return token;
}

void expand_tokens(t_token *token)
{
	t_base base;

	ft_bzero(&base, sizeof(t_base));

	token = handle_command_token(&base, token);
	token = handle_flag_tokens(&base, token);
	token = handle_argument_tokens(&base, token);
	printf("ok");
}
