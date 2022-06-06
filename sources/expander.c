#include "minishell.h"

int is_redirection_operator(t_token *token)
{
	return !strcmp(token->value, ">>")
			|| !strcmp(token->value, ">")
			|| !strcmp(token->value, "<<")
			|| !strcmp(token->value, "<");
}

t_token *handle_redirection_tokens(t_op *base, t_token *token)
{
	while (token
			&& (open_in(base, token) == NOT_SKIP
				|| open_out(base, token) == NOT_SKIP))
		token = token->next->next;
	return token;
}

t_token *handle_command_token(t_op *base, t_token *token)
{
	token = handle_redirection_tokens(base, token);
	if (token && !strcmp(token->value, "echo"))
	{
		token->type = ECHO_TYPE;
		base->function = echo_function;
	}
	else if (token && ft_strchr(token->value, '/'))
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

t_token *handle_flag_tokens(t_op *base, t_token *token)
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

t_token *handle_argument_tokens(t_op *base, t_token *token)
{
	while (token && strcmp(token->value, "|"))
	{
		token = handle_redirection_tokens(base, token);
		if (token && strcmp(token->value, "|"))
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

t_token *handle_pipe_token(t_op *base, t_token *token)
{
	token = handle_redirection_tokens(base, token);
	if (token && !strcmp(token->value, "|"))
	{
		token->type = PIPE;
		token = token->next;
	}
	return token;
}

t_op *expand(t_token *token)
{
	t_op *op;
	t_op *parent;

	op = ft_memalloc(sizeof(t_op));
	op->in = STDIN_FILENO;
	op->out = STDOUT_FILENO;

	token = handle_command_token(op, token);
	token = handle_flag_tokens(op, token);
	token = handle_argument_tokens(op, token);
	if (token && !strcmp(token->value, "|"))
	{
		parent = expand(token->next);
		parent->child = op;
		return parent;
	}
	else
		return op;
}
