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

void while_true(void)
{
	char *buffer;
	int status;

	buffer = NULL;
	while (TRUE)
	{
		buffer = read_from_input();

		lexer(buffer);
		if (status == 666)
			break;
		free(buffer);
	}
}