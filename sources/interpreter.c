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
		close(fd[0]);
		close(fd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
}

void interpreter(t_op *parent)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (parent->command->type == EXIT_TYPE)
		exit(0);
	if (pipe(fd) == 0)
	{
		pid1 = fork();
		if (pid1 == 0)
			run_child_process(fd, parent->child);
		pid2 = fork();
		if (pid2 == 0)
			run_parent_process(fd, parent);
		close(fd[0]);
		close(fd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
}