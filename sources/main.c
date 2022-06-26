#include "minishell.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1 != '\0' && *s2 != '\0')
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	init_singleton(char **envp)
{
	singleton = ft_memalloc(sizeof(t_glob));
	singleton->env = save_envp_to_list(envp);
	singleton->envp_chars = envp;
	singleton->last_exit_status = 1;
	singleton->is_exit = FALSE;
}

void print_real_envp(char **envp)
{
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
}

int main(int argc, char **argv, char **envp)
{

	char *line;

	init_singleton(envp);

//	print_real_envp(envp);
//	printf("\n");
//	ft_lstiter(singleton->env, print_env);

	routine();
	rl_clear_history();
	return (singleton->last_exit_status);
}

void singleton_handle_errors()
{
	singleton->last_exit_status;
}



//int	main(int argc, char **argv, char **envp)
//{
//	t_list *arguments;
//
//	arguments = ft_lstnew("firstarg");
//	ft_lstadd_back(&arguments, ft_lstnew("second=arg"));
//	ft_lstadd_back(&arguments, ft_lstnew("third"));
//	init_singleton(envp);
//	export_function(arguments);
//	print_sorted_list(singleton->g_env);
//	return (0);
//}


