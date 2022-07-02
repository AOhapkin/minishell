/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmyriah <gmyriah@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:43:48 by gmyriah           #+#    #+#             */
/*   Updated: 2022/06/29 21:43:49 by gmyriah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_child_process(int fd[2], t_op *op)
{
	if (op && op->child)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		handle_pipes(op);
	}
	else if (op)
	{
		handle_redir_signals();

		handle_child_redirections(fd, op);
		op->function(op);
		close(fd[0]);
		close(fd[1]);
	}
	exit(0);
}

void	run_parent_process(int fd[2], t_op *op)
{
	handle_redir_signals();
	handle_parent_redirections(fd, op);
	close(fd[0]);
	close(fd[1]);
	if (g_singleton->last_exit_stat)
		exit(0);
	op->function(op);
	exit(0);
}

void set_new_exit(int new_exit_code)
{
	if (!g_singleton->last_exit_stat)
		g_singleton->last_exit_stat = WEXITSTATUS(new_exit_code);
}

void	handle_pipes(t_op *parent)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int 	tmp;

//	if (!g_singleton->last_exit_stat && pipe(fd) == 0)
	if (pipe(fd) == 0)
	{

		pid1 = fork();
		if (pid1 == 0)
		{
//		handle_cmd_signals();
			run_child_process(fd, parent->child);
		}
		waitpid(pid1, &tmp, 0);
		set_new_exit(tmp);

		pid2 = fork();
		if (pid2 == 0)
		{
//			handle_redir_signals();
			run_parent_process(fd, parent);

		}
		close(fd[0]);
		close(fd[1]);
//		waitpid(pid1, &tmp, 0);
//		set_new_exit(tmp);
		waitpid(pid2, &tmp, 0);
		set_new_exit(tmp);
//		printf("hello there mr %i\n", g_singleton->last_exit_stat);
	}
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

void	interpreter(t_op *parent)
{
	handle_cmd_signals();
	g_singleton->last_exit_stat = 0;
	if (parent->child)
		handle_pipes(parent);
	else
		no_pipes_execution(parent);
}
