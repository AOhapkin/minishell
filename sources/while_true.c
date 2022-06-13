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
	while (!is_all_quotes_close(input))
		input = read_from_input_and_join_with_previous(input);
	if (isatty(STDIN_FILENO) && input)
		add_history(input);
	return (input);
}

void free_piped_ops(t_op *parent)
{
	if (parent)
	{
		if (parent->out != STDOUT_FILENO)
			close(parent->out);
		if (parent->in != STDIN_FILENO)
			close(parent->in);
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
	while (TRUE)
	{
		buffer = read_from_input();
		if (!buffer || ft_strlen(buffer) == 0)
			continue;
		tokens = lexer(buffer);
		parent = expand(tokens);
		if (parent != NULL)
		{
			interpreter(parent);
			free_piped_ops(parent);
		}
//		print_all_tokens(tokens);
		free_list_of_tokens(tokens);
		free(buffer);
	}
}