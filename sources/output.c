#include "minishell.h"

int is_redirection_operator_ish(t_token *token)
{
	return !strcmp(token->value, ">>")
		   || !strcmp(token->value, ">")
		   || !strcmp(token->value, "<<")
		   || !strcmp(token->value, "<");
}

int	open_out(t_base *base, t_token *token)
{
	t_token *arg;

	if (!strcmp(token->value, ">")
		|| !strcmp(token->value, ">>"))
	{
		if (base->out != STDOUT_FILENO)
			close(base->out);
		arg = token->next;
		if (!arg || is_redirection_operator_ish(token) || !strcmp(token->value, "|"))
		{
			printf("minishell : syntax error near unexpected token `%s'\n", arg->value ? arg->value : "newline");
			exit(1); // todo переписать
		}
		if (!strcmp(token->value, ">"))
			base->out = open(arg->value, O_RDWR | O_CREAT | O_APPEND, 0644);
		else
			base->out = open(arg->value, O_RDWR | O_CREAT | O_TRUNC, 0644);
		token->type = REDIRECT_OUTPUT;
		base->output = arg;
		arg->type = REDIRECT_ARG_TYPE;
		return NOT_SKIP;
	}
	return SKIP;
}