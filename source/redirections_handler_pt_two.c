/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmyriah <gmyriah@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:44:09 by gmyriah           #+#    #+#             */
/*   Updated: 2022/06/29 21:44:10 by gmyriah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_single_redirection(t_op *op)
{
	handle_cmd_signals();
	if (op->input && op->input->type == HERE_DOCUMENTS)
	{
		handle_here_documents(NULL, op);
	}
	else if (op->input)
		handle_input_from_file_single(op);
	if (op->output)
		handle_output_to_file_single(op);
}

int	is_redirectable_op(t_op *op)
{
	char	op_type;

	op_type = op->command->type;
	return ((op_type == ECHO_TYPE)
		|| (op_type == EXEC_TYPE)
		|| (op_type == PWD_TYPE)
		|| (op_type == EXPORT_TYPE && op->is_contain_args == FALSE));
}

void	no_pipes_execution(t_op *op)
{
	if (is_redirectable_op(op))
		handle_pipes(op);
	else
	{
		handle_single_redirection(op);
		op->function(op);
	}
}
