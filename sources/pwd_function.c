/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmyriah <gmyriah@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:43:58 by gmyriah           #+#    #+#             */
/*   Updated: 2022/06/29 21:44:00 by gmyriah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_function(t_op *op)
{
	char	buffer[256];
	t_op	*operation;

	operation = op;
	if (getcwd(buffer, sizeof(char) * 256))
	{
		printf("%s\n", buffer);
		g_singleton->last_exit_stat = 0;
	}
	else
		g_singleton->last_exit_stat = 1;
}
