#include "minishell.h"

char *get_home_path()
{
	t_list *env_home;
	char	*home_path;

	env_home = find_element_by_key(singleton->env, "HOME");
	if (env_home == NULL)
		printf("minishell > cd: OLDPWD not set\"");
	home_path = ((t_env *)env_home->content)->value;
	return (home_path);
}

void updade_old_pwd()
{
	t_list *pwd_list;
	t_list *old_pwd_list;
	t_env *old_pwd_env;
	t_env *pwd_env;

	pwd_list = find_element_by_key(singleton->env, "PWD");
	if (pwd_list == NULL)
		printf("minishell > cd: PWD not set\"");
	old_pwd_list = find_element_by_key(singleton->env, "OLDPWD");
	if (old_pwd_list == NULL)
		printf("minishell > cd: OLDPWD not set\"");
	pwd_env = pwd_list->content;
	old_pwd_env = old_pwd_list->content;
	if (old_pwd_env->value)
		free(old_pwd_env->value);
	old_pwd_env->value = pwd_env->value;
}

void updade_pwd()
{
	char	current_directory[256];
	t_list	*pwd_list;
	t_env	*pwd_env;

	getcwd(current_directory, 256);
	pwd_list = find_element_by_key(singleton->env, "PWD");
	pwd_env = pwd_list->content;
	pwd_env->value = ft_strdup(current_directory);
}

void	cd_function(t_op *operation)
{
	char	*path;
	int		cd_result;

	if (operation->is_contain_args == FALSE)
		path = get_home_path();
	else
		path = operation->command->next->value;
	if (path)
	{
		updade_old_pwd();
		cd_result = chdir(path);
		if (cd_result == 0)
		{
			updade_pwd();
			return ;
		}
		printf("minishell > cd: %s: No such file or directory\n", path);
	}
}