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
	t_list	*elem;

	while (list)
	{
		if (!ft_strcmp(key, ((t_env *)(list->content))->key))
			return (list);
		list = list->next;
	}
	return (NULL);
}

void	delete_list_element_by_name(t_list **list, const char *param_name)
{
	t_list	*current;
	t_list	*prev;
	t_env	*env_var;

	prev = NULL;
	current = *list;
	while (current)
	{
		env_var = current->content;
		if (!ft_strcmp(param_name, env_var->key))
		{
			if (!prev)
				*list = current->next;
			else
				prev->next = current->next;
			free_env(&env_var);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

t_env	**list_to_array(t_list *list)
{
	t_env	**env;
	int		i;
	int		list_size;

	list_size = ft_lstsize(list);
	env = ft_memalloc((list_size + 1) * sizeof(t_env *));
	i = 0;
	while (list)
	{
		env[i++] = (t_env *)(list->content);
		list = list->next;
	}
	env[i] = NULL;
	return (env);
}

void	print_sorted_list(t_list *list_head)
{
	t_env	**values_array;

	values_array = list_to_array(list_head);
	sort_t_env_array(values_array, ft_lstsize(list_head));
	print_t_env_array(values_array);
	free(values_array);
}
