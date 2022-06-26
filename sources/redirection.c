#include "minishell.h"

int is_redirection_operator_ish(t_token *token)
{
	return !strcmp(token->value, ">>")
		   || !strcmp(token->value, ">")
		   || !strcmp(token->value, "<<")
		   || !strcmp(token->value, "<");
}

int	open_out(t_op *base, t_token *token)
{
	t_token *arg;

	if (!strcmp(token->value, ">")
		|| !strcmp(token->value, ">>"))
	{
		arg = token->next;
		if (!arg || is_redirection_operator_ish(arg) || !strcmp(arg->value, "|"))
		{
			base->is_valid = FALSE;
			printf("minishell : syntax error near unexpected token `%s'\n", arg ? arg->value : "newline");
			return SKIP;
		}
		if (!ft_strcmp(token->value, ">"))
			token->type = REDIRECT_OUTPUT;
		else
			token->type = APPENDING_REDIRECTED_OUTPUT;
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
	while (strcmp(input, arg->value))
	{
		if (input != result)
		{
			result = join_and_free_srcs(result, ft_strdup("\n"));
			result = join_and_free_srcs(result, input);
		}
		input = readline(">");
	}
	free(input);
	free(arg->value);
	arg->value = result;
}

int	open_in(t_op *base, t_token *token)
{
	t_token *arg;

	if (!strcmp(token->value, "<")
		|| !strcmp(token->value, "<<"))
	{
		arg = token->next;
		if (!arg || is_redirection_operator_ish(arg) || !strcmp(arg->value, "|"))
		{
			base->is_valid = FALSE;
			printf("minishell : syntax error near unexpected token `%s'\n", arg ? arg->value : "newline");
			return SKIP;
		}

		if (!ft_strcmp(token->value, "<"))
			token->type = REDIRECT_INPUT;
		else
		{
			update_argument_token(base, arg);
			token->type = HERE_DOCUMENTS;
		}
		base->input = token;
		arg->type = REDIRECT_ARG_TYPE;
		return NOT_SKIP;
	}
	return SKIP;
}