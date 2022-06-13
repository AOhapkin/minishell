#include "minishell.h"

void echo_function(t_op *op)
{
	t_token *arg;
	int is_first;

	if (op->output)
		dup2(op->out, 1);
	arg = op->command->next;
	is_first = TRUE;
	while (arg && strcmp(arg->value, "|"))
	{
		if (arg->type == COMMAND_ARG_TYPE)
		{
			if (is_first)
				is_first = FALSE;
			else
				printf(" ");
			printf("%s", arg->value);
		}
		arg = arg->next;
	}
	if (op->is_contain_flag == FALSE)
		printf("\n");
}
