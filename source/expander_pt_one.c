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

void	free_paths_array(char **paths)
{
	char	**tmp;

	tmp = paths;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(paths);
}

char	*get_path_to_bin(char *name, char *env_path_value)
{
	char	**paths;
	char	*temp;
	char	*full_path;
	int		i;

	paths = ft_split(env_path_value, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		temp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(temp, name);
		free(temp);
		if (!access(full_path, F_OK))
		{
			free_paths_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_paths_array(paths);
	return (NULL);
}

int	is_executable(t_token *token)
{
	t_list	*path_list;
	t_env	*path_env;
	char	*path_to_bin;

	if (ft_strchr(token->value, '/'))
		return (TRUE);
	else
	{
		path_list = find_element_by_key(g_singleton->env, "PATH");
		if (!path_list)
			return (FALSE);
		path_env = path_list->content;
		path_to_bin = get_path_to_bin(token->value, path_env->value);
		if (path_to_bin)
		{
			free(token->value);
			token->value = path_to_bin;
			return (TRUE);
		}
	}
	return (FALSE);
}

t_token	*handle_unexpected_token(t_op *base, t_token *token)
{
	printf("minishell : syntax error near unexpected token `%s'\n",
		token->value);
	g_singleton->last_exit_stat = 258;
	base->is_valid = FALSE;
	return (NULL);
}

t_op	*expand(t_token *token)
{
	t_op	*op;
	t_op	*parent;
	t_op	*tmp;

	if (!token)
		return (NULL);
	op = ft_memalloc(sizeof(t_op));
	op->is_valid = TRUE;
	token = handle_command_token(op, token);
	token = handle_flag_tokens(op, token);
	token = handle_argument_tokens(op, token);
	if (op->is_valid == TRUE && token && token->type == PIPE && token->next)
	{
		parent = expand(token->next);
		if (!parent)
			return (op);
		tmp = parent;
		while (tmp->child)
			tmp = tmp->child;
		tmp->child = op;
		return (parent);
	}
	return (op);
}
