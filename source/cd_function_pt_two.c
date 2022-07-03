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
