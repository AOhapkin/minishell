#include "minishell.h"

void	pwd_function(t_op *op)
{
	char	buffer[256];
	t_op	*operation;

	operation = op;
	if (getcwd(buffer, sizeof(char) * 256))
	{
		printf("%s\n", buffer);
		g_singleton->last_exit_stat = 0;
	}
	else
		g_singleton->last_exit_stat = 1;
}
