#include "minishell.h"

void run_child_process(int fd[2], t_op *op)
{
	int		input_pipe_fd[2];
	char	*input_buff;
	char	*input_file;
	int		input_fd;
	char	*out_file;
	int		out_fd;

	out_fd = 1;
	input_fd = 0;
	if (op && op->child)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		handle_pipes(op);
	} else if (op)
	{
		input_fd = 0;
		if (op->input && op->input->type == HERE_DOCUMENTS)
		{
			pipe(input_pipe_fd);
			input_buff = op->input->next->value;
			dup2(input_pipe_fd[0], 0);
			write(input_pipe_fd[1], input_buff, ft_strlen(input_buff));
			close(input_pipe_fd[0]);
			close(input_pipe_fd[1]);
		}
		else if (op->input && op->input->type == REDIRECT_INPUT)
		{
			input_file = op->input->next->value;
			input_fd = open(input_file, O_RDONLY);
			dup2(input_fd, 0);
		}
		if (op->output)
		{
			out_file = op->output->next->value;
			if (op->output->type == REDIRECT_OUTPUT)
				out_fd = open(out_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
			else
				out_fd = open(out_file, O_RDWR | O_CREAT | O_APPEND, 0644);
			dup2(out_fd, 1);
		}
		else
			dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		op->function(op);
		if (out_fd != 1)
			close(out_fd);
		if (input_fd != 0)
			close(input_fd);
	}
	exit(0);
}


void run_parent_process(int fd[2], t_op *op)
{
	int		input_pipe_fd[2];
	char	*input_buff;
	char	*input_file;
	int		input_fd;
	char	*out_file;
	int		out_fd;

	out_fd = 1;
	input_fd = 0;
	if (op->input && op->input->type == HERE_DOCUMENTS)
	{
		pipe(input_pipe_fd);
		input_buff = op->input->next->value;
		dup2(input_pipe_fd[0], 0);
		write(input_pipe_fd[1], input_buff, ft_strlen(input_buff));
		close(input_pipe_fd[0]);
		close(input_pipe_fd[1]);
	}
	else if (op->input && op->input->type == REDIRECT_INPUT)
	{
		input_file = op->input->next->value;
		input_fd = open(input_file, O_RDONLY);
		// todo нужна проверка на открываемость
		if (input_fd < 0)
			exit(100500);
		dup2(input_fd, 0);
	}
	else
		dup2(fd[0], 0);
	if (op->output)
	{
		out_file = op->output->next->value;
		if (op->output->type == REDIRECT_OUTPUT)
			out_fd = open(out_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
		else
			out_fd = open(out_file, O_RDWR | O_CREAT | O_APPEND, 0644);
		dup2(out_fd, 1);
	}

	close(fd[0]);
	close(fd[1]);
	op->function(op);
	if (out_fd != 1)
		close(out_fd);
	if (input_fd != 0)
		close(input_fd);
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