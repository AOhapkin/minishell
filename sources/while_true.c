#include "minishell.h"

char *read_from_input_and_join_with_previous(char *previous_input)
{
	char	*input;

	input = readline(">");
	previous_input = join_and_free_srcs(previous_input, ft_strdup("\n"));
	input = join_and_free_srcs(previous_input, input);
	if (isatty(STDIN_FILENO) && input)
		add_history(input);
	return (input);
}

int is_all_quotes_close(char *input)
{
	char quote;

	quote = 0;
	while (*input)
	{
		if (ft_strchr(QUOTES, *input) && !quote)
			quote = *input;
		else if (ft_strchr(QUOTES, *input) && *input == quote)
			quote = 0;
		input++;
	}
	if (quote)
		return FALSE;
	else
		return TRUE;
}

char *read_from_input()
{
	char	*input;

	input = readline(PROMPT);
	if (!input)
		return input;
	while (!is_all_quotes_close(input))
		input = read_from_input_and_join_with_previous(input);
	if (isatty(STDIN_FILENO) && input && ft_strlen(input))
		add_history(input);
	return (input);
}

void free_piped_ops(t_op *parent)
{
	if (parent)
	{
		free_piped_ops(parent->child);
		free(parent);
	}
}

void routine(void)
{
	char *buffer;
	t_token *tokens;
	t_op *parent;

	tokens = NULL;
	buffer = NULL;
	// игнорирование (ctrl-\)
//	signal(SIGQUIT, SIG_IGN);
	while (singleton->is_exit == FALSE)
	{
		//ставим обработчик на (ctrl-c)
//		signal(SIGINT, handle_ctrl_c_signal);
		handle_global_signals();
		termios_change(0);
		buffer = read_from_input();
		if (!buffer)
			break;
		if (ft_strlen(buffer) == 0)
		{
			free(buffer);
			continue;
		}
		tokens = lexer(buffer);
		parent = expand(tokens);
		if (parent != NULL && parent->is_valid)
			interpreter(parent);
		free_piped_ops(parent);
//		print_all_tokens(tokens);
		free_list_of_tokens(tokens);
		free(buffer);
	}
}