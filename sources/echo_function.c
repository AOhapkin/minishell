#include "minishell.h"

void echo_function(t_base *base)
{
	t_token *current;
	int is_first;

	is_first = TRUE;
	current = base->command->next;
	while (current)
	{
		if (current->type == COMMAND_ARG_TYPE)
		{
			if (is_first)
				is_first = FALSE;
			else
				printf(" ");
			printf("%s", current->value);
		}
		current = current->next;
	}
	if (base->contain_flag == FALSE)
		printf("\n");
}
