#include "minishell.h"

void env_function(t_op *op)
{
	t_list *current;

	if (op->out != STDOUT_FILENO)
		dup2(op->out, 1);
	current = singleton->env;
	while(current)
	{
		print_env(current->content);
		current = current->next;
	}
}