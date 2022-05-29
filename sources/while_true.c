#include "minishell.h"

char *get_input(void)
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

	while (TRUE)
	{
		// TODO добавить обертку для readline чтобы добавлялось в историю с валидацией
		buffer = get_input();

		status = lexer(buffer);

		free(buffer);
	}
}