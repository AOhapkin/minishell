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

void	init_singleton(char **envp)
{
	singleton = ft_memalloc(sizeof(t_glob));
	singleton->g_env = save_envp_to_list(envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_list *arguments;

	arguments = ft_lstnew("first arg");
	ft_lstadd_back(&arguments, ft_lstnew("second arg"));
	ft_lstadd_back(&arguments, ft_lstnew("third arg"));
	init_singleton(envp);
	print_list(singleton->g_env);
	printf("\n\n!!!!!!!\n\n");
	export_function(arguments);
	print_list(singleton->g_env);
	printf("\n\n!!!!!!!\n\n");
	print_sorted_list(singleton->g_env);
	return (0);
}