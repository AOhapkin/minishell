/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmyriah <gmyriah@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:43:50 by gmyriah           #+#    #+#             */
/*   Updated: 2022/06/29 21:43:51 by gmyriah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quotes(t_lexer *lexer)
{
	if ((!lexer->quote && ft_strchr(QUOTES, *lexer->buffer))
		|| lexer->quote && *lexer->buffer == lexer->quote)
	{
		if (lexer->quote && *lexer->buffer == lexer->quote)
			lexer_update_value_and_quote(lexer, 0);
		else
			lexer_update_value_and_quote(lexer, *lexer->buffer);
		lexer->buffer++;
		lexer->from = lexer->buffer;
		return (NOT_SKIP);
	}
	else
		return (SKIP);
}

int	handle_spaces(t_lexer *lexer)
{
	if (ft_isspace(*lexer->buffer) && !lexer->quote)
	{
		lexer_add_token(lexer);
		while (lexer->buffer && ft_isspace(*lexer->buffer))
			lexer->buffer++;
		lexer->from = lexer->buffer;
		return (NOT_SKIP);
	}
	return (SKIP);
}

int	handle_simple_char(t_lexer *lexer)
{
	lexer->buffer++;
	if (!*lexer->buffer)
	{
		lexer_add_token(lexer);
		lexer->from = lexer->buffer;
	}
	return (NOT_SKIP);
}
