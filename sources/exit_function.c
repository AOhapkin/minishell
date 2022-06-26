#include "minishell.h"

void exit_function(t_op *op)
{
	t_token	*arg;
	int		temp_exit_arg;
	int		i;

	arg = op->command->next;
	i = 0;
	while (arg && ft_strcmp(arg->value, "|"))
	{
		if (i == 0 && ft_isdigit(*(arg->value)))
			temp_exit_arg = ft_atoi(arg->value);
		if (i == 0 && !ft_isdigit(*(arg->value)))
		{
			singleton->last_exit_status = 2;
			singleton->is_exit = TRUE;
			return;
		}
		i++;
		arg = arg->next;
	}
	if (i == 0)
	{
		singleton->last_exit_status = 0;
		singleton->is_exit = TRUE;
	}
	if (i == 1)
	{
		if (temp_exit_arg >= 0 && temp_exit_arg <= 255)
			singleton->last_exit_status = temp_exit_arg;
		else
			singleton->last_exit_status = 255;
		singleton->is_exit = TRUE;
	}
	if (i > 1)
	{
		printf("minishell > exit: too many arguments\n");
		singleton->last_exit_status = 1;
	}
}
