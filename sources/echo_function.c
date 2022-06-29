#include "minishell.h"

void	echo_function(t_op *op)
{
	t_token	*arg;
	int		is_first;

	arg = op->command->next;
	is_first = TRUE;
	while (arg && arg->type != PIPE)
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
	g_singleton->last_exit_stat = 0;
}
