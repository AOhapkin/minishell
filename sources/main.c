#include "minishell.h"

int main(int argc, char **argv, char **envp)
{

	char *line;

	while_true();
	rl_clear_history();
	return 0;
}

//int main(int argc, char **argv)
//{
//	char *s = "hello world";
//	char *from = s;
//	char *to = s;
//
//	printf("|%s|\n", ft_substr(from, 0, to - from));
//	return 0;
//}