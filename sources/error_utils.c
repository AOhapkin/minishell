/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmyriah <gmyriah@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 20:21:38 by toni              #+#    #+#             */
/*   Updated: 2022/06/29 21:43:30 by gmyriah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	getErrCode(int err_code, int is_set_err_code)
{
	static int	static_err_code = 0;

	if (is_set_err_code)
		static_err_code = err_code;
	return (static_err_code);
}

void	set_err_code(int err_code)
{
	static int	is_last_cmd_ctrlc = FALSE;

	if (is_last_cmd_ctrlc)
	{
		is_last_cmd_ctrlc = FALSE;
		return ;
	}
	if (err_code == 130)
		is_last_cmd_ctrlc = FALSE;
	getErrCode(err_code, FALSE);
}

int	get_err_code(void)
{
	return (getErrCode(0, FALSE));
}
