/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmyriah <gmyriah@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:43:43 by gmyriah           #+#    #+#             */
/*   Updated: 2022/06/29 21:43:44 by gmyriah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*handle_argument_tokens(t_op *base, t_token *token)
{
	while (base->is_valid && token && token->type != PIPE)
	{
		token = handle_redirection_tokens(base, token);
		if (token && token->type != PIPE)
		{
			token->type = COMMAND_ARG_TYPE;
			base->is_contain_args = TRUE;
			token = token->next;
		}
		else
			break ;
	}
	return (token);
}
