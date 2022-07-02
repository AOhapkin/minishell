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

void	read_write_heredoc(int fd[2], char *stop_word)
{
	char	*input;
	char	*result;

	result = NULL;
	handle_redir_signals();
	input = readline(">");
	while (input && ft_strcmp(input, stop_word))
	{
		if (result)
		{
			result = join_and_free_srcs(result, ft_strdup("\n"));
			result = join_and_free_srcs(result, input);
		}
		else
			result = input;
		input = readline(">");
	}
	if (input)
	{
		if (result)
		{
			write(fd[1], result, ft_strlen(result));
			write(fd[1], "\n", 1);
			free(result);
		}
		free(input);
	}
	exit(g_singleton->last_exit_stat);
}
//void 	read_write_heredoc(int fd[2], char *stop_word)
//{
//	char	*input;
//
//	input = readline(">");
//	while (input && ft_strcmp(input, stop_word))
//	{
//		write(fd[1], input, ft_strlen(input));
//		write(fd[1], "\n", 1);
//		free(input);
//		input = readline(">");
//	}
//	if (input)
//		free(input);
//	exit(0);
//}

void	handle_here_documents(int prev_fd[2], t_op *parent)
{
	int		fd[2];
	pid_t	pid;
	int 	tmp;

	if (prev_fd && prev_fd[0] != STDIN_FILENO)
		close(prev_fd[0]);
	if (pipe(fd) == 0)
	{
		pid = fork();
		if (pid == 0)
			read_write_heredoc(fd, parent->input->next->value);
		close(fd[1]);
		waitpid(pid, &tmp, 0);
		set_new_exit(tmp);
	}
}

void	handle_input_from_file(int fd[2], t_op *op)
{
	char	*input_file;
	int		input_fd;

	input_file = op->input->next->value;
	input_fd = open(input_file, O_RDONLY);
	if (input_fd == -1)
		printf("-minishell: %s: %s\n", input_file, strerror(errno));
	else
	{
		close(fd[0]);
		fd[0] = input_fd;
	}
}

void	handle_output_to_file(int fd[2], t_op *op)
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
	{
		close(fd[1]);
		fd[1] = out_fd;
	}
}

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
