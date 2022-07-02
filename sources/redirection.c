/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmyriah <gmyriah@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:44:02 by gmyriah           #+#    #+#             */
/*   Updated: 2022/06/29 21:44:07 by gmyriah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection_type(char type)
{
	return (type == REDIRECT_INPUT
		|| type == HERE_DOCUMENTS
		|| type == APPENDING_REDIRECTED_OUTPUT
		|| type == REDIRECT_OUTPUT);
}

int	expand_output_redirection(t_op *base, t_token *token)
{
	t_token	*arg;

	if (token->type == REDIRECT_OUTPUT
		|| token->type == APPENDING_REDIRECTED_OUTPUT)
	{
		arg = token->next;
		if (!arg || arg->type == PIPE || is_redirection_type(arg->type))
		{
			handle_unexpected_token(base, token);
			return (SKIP);
		}
		base->output = token;
		arg->type = REDIRECT_ARG_TYPE;
		return (NOT_SKIP);
	}
	return (SKIP);
}

int	expand_input_redirection(t_op *base, t_token *token)
{
	t_token	*arg;

	if (token->type == REDIRECT_INPUT || token->type == HERE_DOCUMENTS)
	{
		arg = token->next;
		if (!arg || arg->type == PIPE || is_redirection_type(arg->type))
			return (SKIP);
		base->input = token;
		arg->type = REDIRECT_ARG_TYPE;
		return (NOT_SKIP);
	}
	return (SKIP);
}
