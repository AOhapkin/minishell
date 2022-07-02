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
