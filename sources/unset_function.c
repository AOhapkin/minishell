#include "minishell.h"

void unset_if_contains(char *param)
{
	t_list *env_var;

	delete_list_element_by_name(&(singleton->env), param);
}


void	unset_function(t_op *op)
{
	t_token *arg;

	arg = op->command->next;
	while (arg)
	{
		if (arg->type == COMMAND_ARG_TYPE)
			unset_if_contains(arg->value);
		arg = arg->next;
	}
}