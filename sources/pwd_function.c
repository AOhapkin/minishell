#include "minishell.h"

void pwd_function(t_op *op)
{
	char buffer[256];
	t_op *operation;

	operation = op;
	if (getcwd(buffer, sizeof(char) * 256))
	{
		printf("%s\n", buffer);
		singleton->last_exit_status = 0;
	}
	else
		singleton->last_exit_status = 1;
}
