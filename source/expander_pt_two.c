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

t_token	*handle_redirection_tokens(t_op *base, t_token *token)
{
	while (base->is_valid && token
		&& (expand_input_redirection(base, token) == NOT_SKIP
			|| expand_output_redirection(base, token) == NOT_SKIP))
		token = token->next->next;
	return (token);
}

int	commands_pt_two(t_op *base, t_token *token)
{
	if (token && !ft_strcmp(token->value, "pwd"))
	{
		token->type = PWD_TYPE;
		base->function = pwd_function;
		return (TRUE);
	}
	else if (token && !ft_strcmp(token->value, "exit"))
	{
		token->type = EXIT_TYPE;
		base->function = exit_function;
		return (TRUE);
	}
	else if (token && is_executable(token))
	{
		token->type = EXEC_TYPE;
		base->function = exec_function;
		return (TRUE);
	}
	else if (token && !ft_strcmp(token->value, "unset"))
	{
		token->type = UNSET_TYPE;
		base->function = unset_function;
		return (TRUE);
	}
	return (FALSE);
}

int	commands_pt_one(t_op *base, t_token *token)
{
	if (token && !ft_strcmp(token->value, "echo"))
	{
		token->type = ECHO_TYPE;
		base->function = echo_function;
		return (TRUE);
	}
	else if (token && !ft_strcmp(token->value, "export"))
	{
		token->type = EXPORT_TYPE;
		base->function = export_function;
		return (TRUE);
	}
	else if (token && !ft_strcmp(token->value, "cd"))
	{
		token->type = CD_TYPE;
		base->function = cd_function;
		return (TRUE);
	}
	else if (token && !ft_strcmp(token->value, "env"))
	{
		token->type = ENV_TYPE;
		base->function = env_function;
		return (TRUE);
	}
	return (FALSE);
}

t_token	*handle_command_token(t_op *base, t_token *token)
{
	token = handle_redirection_tokens(base, token);
	base->command = token;
	if (token->type == PIPE)
		return (handle_unexpected_token(base, token));
	if (commands_pt_one(base, token)
		|| commands_pt_two(base, token))
		return (token->next);
	else
	{
		if (token->value)
			printf("minishell : %s: command not found\n", token->value);
		else
			printf("minishell : %s: command not found\n", "newline");
		g_singleton->last_exit_stat = 127;
		base->is_valid = FALSE;
		return (NULL);
	}
}

t_token	*handle_flag_tokens(t_op *base, t_token *token)
{
	while (base->is_valid && token && !base->is_contain_args
		&& base->command->type == ECHO_TYPE)
	{
		token = handle_redirection_tokens(base, token);
		if (token && !ft_strcmp(token->value, "-n"))
		{
			token->type = ECHO_N_FLAG;
			base->is_contain_flag = TRUE;
			token = token->next;
		}
		else
			break ;
	}
	return (token);
}
