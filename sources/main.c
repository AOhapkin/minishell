#include "minishell.h"

//int main(int argc, char **argv, char **envp)
//{
//
//	char *line;
//
//	while_true();
//	rl_clear_history();
//	return 0;
//}

int	main(int argc, char **argv, char **envp)
{
	singleton = ft_memalloc(sizeof(t_glob));
	singleton->g_env = save_envp_to_list(envp);
	print_list(singleton->g_env);
	printf("\n\n!!!!!!!\n\n");
	print_sorted_list(singleton->g_env);
	return (0);
}