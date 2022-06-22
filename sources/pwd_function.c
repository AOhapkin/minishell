#include "minishell.h"

void pwd_function(t_op *op)
{
	char buffer[256];

	getcwd(buffer, sizeof(char) * 256);
	printf("%s\n", buffer);
}