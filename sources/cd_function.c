/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_function.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmyriah <gmyriah@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:43:17 by gmyriah           #+#    #+#             */
/*   Updated: 2022/06/29 21:43:19 by gmyriah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "minishell.h"

void	set_empty_oldpwd(t_list *old_pwd_list, t_env *old_pwd_env)
{
	old_pwd_env = old_pwd_list->content;
	if (old_pwd_env->value)
		free(old_pwd_env->value);
	old_pwd_env->value = ft_strdup("");
}

void	set_new_pwd(t_list *pwd_list, t_env *pwd_env, char *current_directory)
{
	pwd_env = pwd_list->content;
	if (pwd_env->value)
		free(pwd_env->value);
	pwd_env->value = ft_strdup(current_directory);
}

void	set_pwd_and_oldpwd(t_env *pwd_env, t_env *oldpwd_env, char *dir)
{
	if (oldpwd_env->value)
		free(oldpwd_env->value);
	oldpwd_env->value = pwd_env->value;
	pwd_env->value = ft_strdup(dir);
}

void	update_pwd(void)
{
	char	current_directory[256];
	t_list	*pwd_list;
	t_env	*pwd_env;
	t_list	*oldpwd_list;
	t_env	*oldpwd_env;

	if (getcwd(current_directory, 256))
	{
		pwd_list = find_element_by_key(g_singleton->env, "PWD");
		oldpwd_list = find_element_by_key(g_singleton->env, "OLDPWD");
		if (pwd_list && oldpwd_list)
		{
			pwd_env = pwd_list->content;
			oldpwd_env = oldpwd_list->content;
			set_pwd_and_oldpwd(pwd_env, oldpwd_env, current_directory);
		}
		else if (oldpwd_list)
			set_empty_oldpwd(oldpwd_list, oldpwd_env);
		else if (pwd_list)
		{
			set_new_pwd(pwd_list, pwd_env, current_directory);
		}
	}
}

char	*get_home_path(void)
{
	t_list	*env_home;
	char	*home_path;

	env_home = find_element_by_key(g_singleton->env, "HOME");
	if (env_home == NULL)
	{
		printf("minishell > cd: HOME not set\n");
		return (NULL);
	}
	home_path = ((t_env *)env_home->content)->value;
	return (home_path);
}

void	go_to_oldpwd(void)
{
	t_list	*env_oldpwd;
	char	*oldpwd_path;

	env_oldpwd = find_element_by_key(g_singleton->env, "OLDPWD");
	if (env_oldpwd == NULL)
	{
		printf("cd: OLDPWD not set\n");
		g_singleton->last_exit_stat = 1;
		return ;
	}
	oldpwd_path = ((t_env *)env_oldpwd->content)->value;
	if (ft_strlen(oldpwd_path) == 1)
	{
		printf("cd: OLDPWD not set\n");
		g_singleton->last_exit_stat = 1;
		return ;
	}
	chdir(oldpwd_path);
	g_singleton->last_exit_stat = 0;
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
			update_pwd();
			return ;
		}
		if (chdir(path) == 0)
		{
			update_pwd();
			g_singleton->last_exit_stat = 0;
			return ;
		}
		printf("minishell > cd: %s: %s\n", path, strerror(errno));
		g_singleton->last_exit_stat = 1;
	}
}
