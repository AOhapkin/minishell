/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmyriah <gmyriah@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:43:25 by gmyriah           #+#    #+#             */
/*   Updated: 2022/06/29 21:43:26 by gmyriah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_function(t_op *op)
{
	t_list	*current;

	current = g_singleton->env;
	while (op && current)
	{
		print_env(current->content);
		current = current->next;
	}
	g_singleton->last_exit_stat = 0;
}
