#include "minishell.h"

char *get_input(char *previous_input)
{
	char	*input;

	input = readline(PROMPT);
	if (previous_input)
		previous_input = join_and_free_srcs(previous_input, "\n");
	input = join_and_free_srcs(previous_input, input);
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
		// TODO добавить обертку для readline чтобы добавлялось в историю с валидацией
		buffer = get_input(NULL);

		buffer = lexer(buffer);
		if (status == 666)
			break;
		free(buffer);
	}
}