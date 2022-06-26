#include "minishell.h"

void update_pwd()
{
	char	current_directory[256];
	t_list	*pwd_list;
	t_env	*pwd_env;
	t_list *old_pwd_list;
	t_env *old_pwd_env;


	if (getcwd(current_directory, 256))
	{
		pwd_list = find_element_by_key(singleton->env, "PWD");
		old_pwd_list = find_element_by_key(singleton->env, "OLDPWD");
		if (pwd_list && old_pwd_list)
		{
			pwd_env = pwd_list->content;
			old_pwd_env = old_pwd_list->content;
			if (old_pwd_env->value)
				free(old_pwd_env->value);
			old_pwd_env->value = pwd_env->value;
			pwd_env->value = ft_strdup(current_directory);
		}
		else if (old_pwd_list)
		{
			old_pwd_env = old_pwd_list->content;
			if (old_pwd_env->value)
				free(old_pwd_env->value);
			old_pwd_env->value = ft_strdup("");
		}
		else if (pwd_list)
		{
			pwd_env = pwd_list->content;
			if (pwd_env->value)
				free(pwd_env->value);
			pwd_env->value = ft_strdup(current_directory);
		}
	}
}

char *get_home_path()
{
	t_list *env_home;
	char	*home_path;

	env_home = find_element_by_key(singleton->env, "HOME");
	if (env_home == NULL)
	{
		printf("minishell > cd: HOME not set\n");
		return NULL;
	}
	home_path = ((t_env *)env_home->content)->value;
	return (home_path);
}

void go_to_oldpwd()
{
	t_list	*env_oldpwd;
	char	*oldpwd_path;

	env_oldpwd = find_element_by_key(singleton->env, "OLDPWD");
	if (env_oldpwd == NULL)
	{
		printf("cd: OLDPWD not set\n");
		singleton->last_exit_status = 1;
		return ;
	}
	oldpwd_path = ((t_env *)env_oldpwd->content)->value;
	if (ft_strlen(oldpwd_path) == 1)
	{
		printf("cd: OLDPWD not set\n");
		singleton->last_exit_status = 1;
		return ;
	}
	chdir(oldpwd_path);
	update_pwd();
	singleton->last_exit_status = 0;
}

void	cd_function(t_op *operation)
{
	char	*path;

	if (operation->is_contain_args == FALSE)
		path = get_home_path();
	else
		path = operation->command->next->value;
	if (path)
	{
		if (!ft_strcmp(path, "-"))
		{
			go_to_oldpwd();
			return ;
		}
		if (chdir(path) == 0) // переход в папку
		{
			update_pwd();
			singleton->last_exit_status = 0;
			return ;
		}
		printf("minishell > cd: %s: No such file or directory\n", path);
		singleton->last_exit_status = 1;
	}
	else
		singleton->last_exit_status = 1;
}