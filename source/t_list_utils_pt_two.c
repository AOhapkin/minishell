/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmyriah <gmyriah@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:44:21 by gmyriah           #+#    #+#             */
/*   Updated: 2022/06/29 21:44:22 by gmyriah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(void *env)
{
	char	*key;
	char	*value;

	key = ((t_env *)env)->key;
	value = ((t_env *)env)->value;
	if (value)
		printf("%s=%s\n", key, value);
}

t_list	*save_envp_to_list(char **envp)
{
	t_list	*result;
	t_list	*new_element;
	t_env	*env;
	int		i;

	i = 0;
	result = NULL;
	while (envp[i])
	{
		env = new_env_by_envp(envp[i]);
		new_element = ft_lstnew(env);
		ft_lstadd_back(&result, new_element);
		i++;
	}
	return (result);
}

t_list	*find_element_by_key(t_list *list, char *key)
{
	while (list)
	{
		if (!ft_strcmp(key, ((t_env *)(list->content))->key))
			return (list);
		list = list->next;
	}
	return (NULL);
}
