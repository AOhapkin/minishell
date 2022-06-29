/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmyriah <gmyriah@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:44:29 by gmyriah           #+#    #+#             */
/*   Updated: 2022/06/29 21:44:30 by gmyriah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_if_contains(char *param)
{
	t_list	*env_var;

	delete_list_element_by_name(&(g_singleton->env), param);
}

void	unset_function(t_op *op)
{
	t_token	*arg;

	arg = op->command->next;
	while (arg)
	{
		if (arg->type == COMMAND_ARG_TYPE)
			unset_if_contains(arg->value);
		arg = arg->next;
	}
	g_singleton->last_exit_stat = 0;
}
