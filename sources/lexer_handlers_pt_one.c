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

int	handle_env_char(t_lexer *lexer)
{
	if (*lexer->buffer == ENV_CHAR
		&& (!lexer->quote || lexer->quote == DOUBLE_QUOTE)
		&& (is_valid_char_for_env_var_name(lexer->buffer[1])))
	{
		lexer_update_value_and_quote(lexer, lexer->quote);
		lexer_add_env_to_value_and_skip_name(lexer);
		return (NOT_SKIP);
	}
	else
		return (SKIP);
}

char	get_redir_type(char *value)
{
	if (!ft_strcmp("<", value))
		return (REDIRECT_INPUT);
	else if (!ft_strcmp(">", value))
		return (REDIRECT_OUTPUT);
	else if (!ft_strcmp(">>", value))
		return (APPENDING_REDIRECTED_OUTPUT);
	else if (!ft_strcmp("<<", value))
		return (HERE_DOCUMENTS);
	else if (!ft_strcmp("|", value))
		return (PIPE);
	return (0);
}

int	handle_redirect(t_lexer *lexer)
{
	t_token	*token;

	if (ft_strchr(REDIRECTIONS_CHARS, *lexer->buffer)
		&& !lexer->quote)
	{
		lexer_add_token(lexer);
		if (!ft_strncmp(lexer->buffer, "<<", 2)
			|| !ft_strncmp(lexer->buffer, ">>", 2))
			lexer->buffer += 2;
		else
			lexer->buffer += 1;
		token = lexer_add_token(lexer);
		token->type = get_redir_type(token->value);
		return (NOT_SKIP);
	}
	else
		return (SKIP);
}
