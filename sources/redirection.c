#include "minishell.h"

int is_redirection_type(char type)
{
	return type == REDIRECT_INPUT
		   || type == HERE_DOCUMENTS
		   || type == APPENDING_REDIRECTED_OUTPUT
		   || type == REDIRECT_OUTPUT;
}

int	expand_output_redirection(t_op *base, t_token *token)
{
	t_token *arg;

	if (token->type == REDIRECT_OUTPUT || token->type == APPENDING_REDIRECTED_OUTPUT)
	{
		arg = token->next;
		if (!arg || arg->type == PIPE || is_redirection_type(arg->type))
		{
//			base->is_valid = FALSE;
//			printf("minishell : syntax error near unexpected token `%s'\n", arg ? arg->value : "newline");
//			singleton->last_exit_status = 258;
			handle_unexpected_token(base, token);
			return SKIP;
		}
		base->output = token;
		arg->type = REDIRECT_ARG_TYPE;
		return NOT_SKIP;
	}
	return SKIP;
}

void update_argument_token(t_op *base, t_token *arg)
{
	char	*input;
	char	*result;

	result = readline(">");
	input = result;
	while (input && ft_strcmp(input, arg->value))
	{
		if (input != result)
		{
			result = join_and_free_srcs(result, ft_strdup("\n"));
			result = join_and_free_srcs(result, input);
		}
		input = readline(">");
	}
	if (input)
		free(input);
	free(arg->value);
	arg->value = result;
}

int	expand_input_redirection(t_op *base, t_token *token)
{
	t_token *arg;

	if (token->type == REDIRECT_INPUT || token->type == HERE_DOCUMENTS)
	{
		arg = token->next;
		if (!arg || arg->type == PIPE || is_redirection_type(arg->type))
		{
			handle_unexpected_token;
			return SKIP;
		}
		if (token->type == HERE_DOCUMENTS)
			update_argument_token(base, arg);
		base->input = token;
		arg->type = REDIRECT_ARG_TYPE;
		return NOT_SKIP;
	}
	return SKIP;
}