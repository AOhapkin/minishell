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
		if (base->out != STDOUT_FILENO)
			close(base->out);
		arg = token->next;
		if (!arg || is_redirection_operator_ish(arg) || !strcmp(arg->value, "|"))
		{
			printf("minishell : syntax error near unexpected token `%s'\n", arg->value ? arg->value : "newline");
			exit(1); // todo переписать
		}
		if (!strcmp(token->value, ">"))
			base->out = open(arg->value, O_RDWR | O_CREAT | O_TRUNC, 0644);
		else
			base->out = open(arg->value, O_RDWR | O_CREAT | O_APPEND, 0644);
		token->type = REDIRECT_OUTPUT;
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
		if (base->in != STDIN_FILENO)
			close(base->in);

		arg = token->next;
		if (!arg || is_redirection_operator_ish(arg) || !strcmp(arg->value, "|"))
		{
			printf("minishell : syntax error near unexpected token `%s'\n", arg->value ? arg->value : "newline");
			exit(1); // todo переписать
		}

		if (!strcmp(token->value, ">"))
			base->in = open(arg->value, O_RDWR | O_CREAT | O_TRUNC, 0644);
		else
			update_argument_token(base, arg);
		token->type = REDIRECT_INPUT;
		base->input = token;
		arg->type = REDIRECT_ARG_TYPE;
		return NOT_SKIP;
	}
	return SKIP;
}