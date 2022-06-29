/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmyriah <gmyriah@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:44:15 by gmyriah           #+#    #+#             */
/*   Updated: 2022/06/29 21:44:16 by gmyriah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env_by_key_value(char *key, char *value)
{
	t_env	*env;

	env = ft_memalloc(sizeof(t_env));
	env->key = key;
	env->value = value;
	return (env);
}

void	free_env(t_env **env)
{
	if (*env)
	{
		if ((*env)->key)
			free((*env)->key);
		if ((*env)->value)
			free((*env)->value);
		(*env)->key = NULL;
		(*env)->value = NULL;
		free(*env);
		*env = NULL;
	}
}

t_env	*new_env_by_envp(char *string)
{
	char	**key_value;
	t_env	*env;

	key_value = ft_split(string, '=');
	env = new_env_by_key_value(key_value[0], key_value[1]);
	free(key_value);
	return (env);
}
