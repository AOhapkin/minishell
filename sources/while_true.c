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

char *read_from_input()
{
	char	*input;

	input = readline(PROMPT);
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

		buffer = lexer(buffer);
		if (status == 666)
			break;
		free(buffer);
	}
}