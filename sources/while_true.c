#include "minishell.h"

void while_true(void)
{
	char *buffer;
	int status;

	while (TRUE)
	{
		// TODO добавить обертку для readline чтобы добавлялось в историю с валидацией
		buffer = readline(PROMPT);

		status = lexer(buffer);

		free(buffer);
	}
}