/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmyriah <gmyriah@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:43:14 by gmyriah           #+#    #+#             */
/*   Updated: 2022/06/29 21:43:16 by gmyriah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_t_env_array(t_env **array, int array_size)
{
	int		is_ordered;
	int		i;
	t_env	*tmp;

	is_ordered = FALSE;
	while (array && is_ordered == 0)
	{
		is_ordered = TRUE;
		i = 0;
		while (i < array_size - 1)
		{
			if (ft_strcmp(array[i]->key, array[i + 1]->key) > 0)
			{
				tmp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tmp;
				is_ordered = FALSE;
			}
			i++;
		}
		array_size--;
	}
}

void	print_name_and_value(t_env *env_var)
{
	printf("%s", env_var->key);
	if (env_var->value)
	{
		printf("=\"%s\"", env_var->value);
	}
	printf("\n");
}

void	print_t_env_array(t_env **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("declare -x ");
		print_name_and_value(array[i]);
		i++;
	}
}
