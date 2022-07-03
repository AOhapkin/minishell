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

void	handle_child_redirections(int fd[2], t_op *op)
{
	if (op->input && op->input->type == HERE_DOCUMENTS)
	{
		handle_here_documents(fd, op);
		dup2(fd[0], 0);
	}
	else if (op->input && op->input->type == REDIRECT_INPUT)
	{
		handle_input_from_file(fd, op);
		dup2(fd[0], 0);
	}
	if (op->output)
		handle_output_to_file(fd, op);
	dup2(fd[1], 1);
}

void	handle_parent_redirections(int fd[2], t_op *op)
{
	int	tmp;

	if (op->input && op->input->type == HERE_DOCUMENTS)
	{
		handle_here_documents(fd, op);
		dup2(fd[0], 0);
	}
	else
	{
		tmp = fd[0];
		if (op->input && op->input->type == REDIRECT_INPUT)
			handle_input_from_file(fd, op);
		if (tmp != fd[0] || op->child)
			dup2(fd[0], 0);
	}
	if (op->output)
	{
		handle_output_to_file(fd, op);
		dup2(fd[1], 1);
	}
}

void	handle_input_from_file_single(t_op *op)
{
	char	*input_file;
	int		input_fd;

	input_file = op->input->next->value;
	input_fd = open(input_file, O_RDONLY);
	if (input_fd == -1)
		printf("-minishell: %s: %s\n", input_file, strerror(errno));
	else
		close(input_fd);
}

void	handle_output_to_file_single(t_op *op)
{
	char	*out_file;
	int		out_fd;

	out_file = op->output->next->value;
	if (op->output->type == REDIRECT_OUTPUT)
		out_fd = open(out_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		out_fd = open(out_file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (out_fd == -1)
		printf("-minishell: %s: %s\n", out_file, strerror(errno));
	else
		close(out_fd);
}
