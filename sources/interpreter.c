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
		handle_child_redirections(fd, op);
		op->function(op);
		close(fd[0]);
		close(fd[1]);
	}
	exit(0);
}

void	run_parent_process(int fd[2], t_op *op)
{
	handle_parent_redirections(fd, op);
	close(fd[0]);
	close(fd[1]);
	op->function(op);
	exit(0);
}

void	handle_pipes(t_op *parent)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == 0)
	{
		handle_cmd_signals();
		pid1 = fork();
		if (pid1 == 0)
			run_child_process(fd, parent->child);
		pid2 = fork();
		if (pid2 == 0)
			run_parent_process(fd, parent);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid1, &(g_singleton->last_exit_stat), 0);
		g_singleton->last_exit_stat = WEXITSTATUS(g_singleton->last_exit_stat);
		waitpid(pid2, &(g_singleton->last_exit_stat), 0);
		g_singleton->last_exit_stat = WEXITSTATUS(g_singleton->last_exit_stat);
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
	if (parent->child)
		handle_pipes(parent);
	else
		no_pipes_execution(parent);
	singleton_handle_errors();
}
