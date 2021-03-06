/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_token_utils_part_one.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmyriah <gmyriah@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:44:24 by gmyriah           #+#    #+#             */
/*   Updated: 2022/06/29 21:44:25 by gmyriah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *value)
{
	t_token	*new;

	new = ft_memalloc(sizeof(t_token));
	if (new)
		new->value = value;
	return (new);
}

int	get_size(t_token *head)
{
	int	len;

	len = 0;
	while (head != NULL)
	{
		head = head->next;
		len++;
	}
	return (len);
}

void	free_list_of_tokens(t_token *head)
{
	t_token	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}

t_token	*get_last_token(t_token *head)
{
	while (head->next)
		head = head->next;
	return (head);
}
