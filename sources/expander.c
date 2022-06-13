#include "minishell.h"

t_token *handle_redirection_tokens(t_op *base, t_token *token)
{
	while (base->is_valid && token
			&& (open_in(base, token) == NOT_SKIP
				|| open_out(base, token) == NOT_SKIP))
		token = token->next->next;
	return token;
}

t_token *handle_command_token(t_op *base, t_token *token)
{
	token = handle_redirection_tokens(base, token);
	base->command = token;
	if (token && !strcmp(token->value, "echo"))
	{
		token->type = ECHO_TYPE;
		base->function = echo_function;
	}
	else if (token && !strcmp(token->value, "export"))
	{
		token->type = EXPORT_TYPE;
		base->function = export_function;
	}
	else if (token && !strcmp(token->value, "cd"))
	{
		token->type = CD_TYPE;
		base->function = cd_function;
	}
	else if (token && !strcmp(token->value, "env"))
	{
		token->type = ENV_TYPE;
		base->function = env_function;
	}
	else if (token && !strcmp(token->value, "unset"))
	{
		token->type = UNSET_TYPE;
		base->function = unset_function;
	}
	else if (token && !strcmp(token->value, "exit"))
		token->type = EXIT_TYPE;
	else if (token && ft_strchr(token->value, '/'))
		token->type = EXEC_TYPE;
	else
	{
		printf("minishell : %s: command not found\n", token->value ? token->value : "newline");
		base->is_valid = FALSE;
		return NULL;
	}
	return token->next;
}

t_token *handle_flag_tokens(t_op *base, t_token *token)
{
	while (base->is_valid && token && !base->is_contain_args && base->command->type == ECHO_TYPE)
	{
		token = handle_redirection_tokens(base, token);
		if (token && !strcmp(token->value, "-n"))
		{
			token->type = ECHO_N_FLAG;
			base->is_contain_flag = TRUE;
			token = token->next;
		}
		else
			break;
	}
	return token;
}

t_token *handle_argument_tokens(t_op *base, t_token *token)
{
	while (base->is_valid && token && strcmp(token->value, "|"))
	{
		token = handle_redirection_tokens(base, token);
		if (token && strcmp(token->value, "|"))
		{
			token->type = COMMAND_ARG_TYPE;
			base->is_contain_args = TRUE;
			token = token->next;
		}
		else
			break;
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
	op->is_valid = TRUE;

	token = handle_command_token(op, token);
	token = handle_flag_tokens(op, token);
	token = handle_argument_tokens(op, token);
	if (op->is_valid == FALSE)
	{
		free(op);
		return NULL;
	}
	if (token && !strcmp(token->value, "|") && token->next)
	{
		token->type = PIPE;
		parent = expand(token->next);
		if (parent == NULL || parent->is_valid == FALSE)
		{
			free(op);
			return NULL;
		}
		parent->child = op;
		return parent;
	}
	else
		return op;
}
