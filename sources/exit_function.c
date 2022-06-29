/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmyriah <gmyriah@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:43:40 by gmyriah           #+#    #+#             */
/*   Updated: 2022/06/29 21:43:41 by gmyriah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_singleton(int i, int temp_arg)
{
	if (i == 0)
	{
		g_singleton->last_exit_stat = 0;
		g_singleton->is_exit = TRUE;
	}
	if (i == 1)
	{
		if (temp_arg >= 0 && temp_arg <= 255)
			g_singleton->last_exit_stat = temp_arg;
		else
			g_singleton->last_exit_stat = 255;
		g_singleton->is_exit = TRUE;
	}
	if (i > 1)
	{
		printf("minishell > exit: too many arguments\n");
		g_singleton->last_exit_stat = 1;
	}
}

void	exit_function(t_op *op)
{
	t_token	*arg;
	int		temp_exit_arg;
	int		i;

	arg = op->command->next;
	i = 0;
	while (arg && arg->type != PIPE)
	{
		if (i == 0 && ft_isdigit(*(arg->value)))
			temp_exit_arg = ft_atoi(arg->value);
		if (i == 0 && !ft_isdigit(*(arg->value)))
		{
			g_singleton->last_exit_stat = 2;
			g_singleton->is_exit = TRUE;
			return ;
		}
		i++;
		arg = arg->next;
	}
	update_singleton(i, temp_exit_arg);
}
