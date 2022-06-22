#include "minishell.h"


void run_child_process(int fd[2], t_op *child)
{
	if (child)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		if (child->child)
			handle_pipes(child);
		else
			child->function(child);
	}
	exit(0);
}


void run_parent_process(int fd[2], t_op *parent)
{
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
	parent->function(parent);
	exit(0);
}


void handle_pipes(t_op *parent)
{

	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == 0)
	{
		pid1 = fork();
		if (pid1 == 0)
			run_child_process(fd, parent->child);
		pid2 = fork();
		if (pid2 == 0)
			run_parent_process(fd, parent);
		if (fd[0] != STDOUT_FILENO && fd[0] != STDIN_FILENO)
			close(fd[0]);
		if (fd[1] != STDOUT_FILENO && fd[1] != STDIN_FILENO)
			close(fd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
}

int is_redirectable_op(t_op *op)
{
	char op_type;
	op_type = op->command->type;
	return (op_type == ECHO_TYPE)
			|| op_type == EXEC_TYPE
			|| (op_type == PWD_TYPE)
			|| (op_type == EXPORT_TYPE && op->is_contain_args == FALSE);
}

void no_pipes_execution(t_op *op)
{
	if (is_redirectable_op(op))
		handle_pipes(op);
	else
		op->function(op);
}

void interpreter(t_op *parent)
{
//	if (parent->child)
		handle_pipes(parent);
//	else
//		no_pipes_execution(parent);
}