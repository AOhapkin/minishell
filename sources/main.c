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
//	char *buffer;
//	int i = 1;
//
//	printf("Количество аргументов = %i\n", argc - 1);
//	while (i < (argc - 1))
//	{
//		printf("- аргумент %i = '%s'\n", i, argv[i]);
//		i++;
//	}
//
//	buffer = readline(PROMPT);
//	printf("Из RPOMPT достал '%s'\n", buffer);
//	free(buffer);
//	return 0;
//}