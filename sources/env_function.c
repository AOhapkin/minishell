#include "minishell.h"

void env_function(t_op *op)
{
	t_list *current;

	current = singleton->env;
	while(current)
	{
		print_env(current->content);
		current = current->next;
	}
	singleton->last_exit_status = 0;
}