#include "minishell.h"

void handle_here_documents(int fd[2], t_op *op)
{
	int input_pipe_fd[2];
	char *input_buff;

	pipe(input_pipe_fd);
	input_buff = op->input->next->value;
	dup2(input_pipe_fd[0], 0);
	write(input_pipe_fd[1], input_buff, ft_strlen(input_buff));
	close(input_pipe_fd[0]);
	close(input_pipe_fd[1]);
}

void handle_input_from_file(int fd[2], t_op *op)
{
	char *input_file;
	int input_fd;

	input_file = op->input->next->value;
	input_fd = open(input_file, O_RDONLY);
	// todo нужна проверка на открываемость
	if (input_fd < 0)
		exit(100500);
	close(fd[0]);
	fd[0] = input_fd;
}

void handle_output_to_file(int fd[2], t_op *op)
{
	char *out_file;
	int out_fd;

	out_file = op->output->next->value;
	if (op->output->type == REDIRECT_OUTPUT)
		out_fd = open(out_file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		out_fd = open(out_file, O_RDWR | O_CREAT | O_APPEND, 0644);
	// todo обработать ошибку
	if (out_fd < 0)
		exit(100500);
	close(fd[1]);
	fd[1] = out_fd;
}

void handle_child_redirections(int fd[2], t_op *op)
{
	if (op->input && op->input->type == HERE_DOCUMENTS)
		handle_here_documents(fd, op);
	else if (op->input && op->input->type == REDIRECT_INPUT)
	{
		handle_input_from_file(fd, op);
		dup2(fd[0], 0);
	}
	if (op->output)
		handle_output_to_file(fd, op);
	dup2(fd[1], 1);
}

void handle_parent_redirections(int fd[2], t_op *op)
{
	if (op->input && op->input->type == HERE_DOCUMENTS)
		handle_here_documents(fd, op);
	else
	{
		if (op->input && op->input->type == REDIRECT_INPUT)
			handle_input_from_file(fd, op);
		dup2(fd[0], 0);
	}
	if (op->output)
	{
		handle_output_to_file(fd, op);
		dup2(fd[1], 1);
	}
}