#include "minishell.h"

void	env_function(t_op *op)
{
	t_list	*current;

	current = g_singleton->env;
	while (current)
	{
		print_env(current->content);
		current = current->next;
	}
	g_singleton->last_exit_stat = 0;
}
