#include "minishell.h"

t_token *handle_redirection_tokens(t_op *base, t_token *token)
{
	while (base->is_valid && token
			&& (expand_input_redirection(base, token) == NOT_SKIP
				|| expand_output_redirection(base, token) == NOT_SKIP))
		token = token->next->next;
	return token;
}

free_paths_array(char **paths)
{
	char **tmp;

	tmp = paths;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(paths);
}

char *get_path_to_bin(char *name, char *env_path_value)
{
	char **paths;
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
	return NULL;
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
		path_list = find_element_by_key(singleton->env, "PATH");
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
	return FALSE;
}

t_token *handle_unexpected_token(t_op *base, t_token *token)
{
	printf("minishell : syntax error near unexpected token `%s'\n", token->value);
	singleton->last_exit_status = 258;
	base->is_valid = FALSE;
	return NULL;
}

t_token *handle_command_token(t_op *base, t_token *token)
{
	token = handle_redirection_tokens(base, token);
	base->command = token;
	if (token->type == PIPE)
		return handle_unexpected_token(base, token);
	if (token && !strcmp(token->value, "echo"))
	{
		token->type = ECHO_TYPE;
		base->function = echo_function;
	}
	else if (token && !strcmp(token->value, "export"))
	{
		token->type = EXPORT_TYPE;
		base->function = export_function;
	}
	else if (token && !strcmp(token->value, "cd"))
	{
		token->type = CD_TYPE;
		base->function = cd_function;
	}
	else if (token && !strcmp(token->value, "env"))
	{
		token->type = ENV_TYPE;
		base->function = env_function;
	}
	else if (token && !strcmp(token->value, "unset"))
	{
		token->type = UNSET_TYPE;
		base->function = unset_function;
	}
	else if (token && !strcmp(token->value, "pwd"))
	{
		token->type = PWD_TYPE;
		base->function = pwd_function;
	}
	else if (token && !strcmp(token->value, "exit"))
	{
		token->type = EXIT_TYPE;
		base->function = exit_function;
	}
	else if (token && is_executable(token))
	{
		token->type = EXEC_TYPE;
		base->function = exec_function;
	}
	else
	{
		printf("minishell : %s: command not found\n", token->value ? token->value : "newline");
		singleton->last_exit_status = 127;
		base->is_valid = FALSE;
		return NULL;
	}
	return token->next;
}

t_token *handle_flag_tokens(t_op *base, t_token *token)
{
	while (base->is_valid && token && !base->is_contain_args && base->command->type == ECHO_TYPE)
	{
		token = handle_redirection_tokens(base, token);
		if (token && !ft_strcmp(token->value, "-n"))
		{
			token->type = ECHO_N_FLAG;
			base->is_contain_flag = TRUE;
			token = token->next;
		}
		else
			break;
	}
	return token;
}

t_token *handle_argument_tokens(t_op *base, t_token *token)
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
			break;
	}
	return token;
}

t_op *expand(t_token *token)
{
	t_op *op;
	t_op *parent;
	t_op *tmp;

	if (!token)
		return NULL;
	op = ft_memalloc(sizeof(t_op));
	op->is_valid = TRUE;

	token = handle_command_token(op, token);
	token = handle_flag_tokens(op, token);
	token = handle_argument_tokens(op, token);
	if (op->is_valid == TRUE
		&& token
		&& token->type == PIPE
		&& token->next)
	{
		parent = expand(token->next);
		if (!parent)
			return op;
		tmp = parent;
		while (tmp->child)
			tmp = tmp->child;
		tmp->child = op;
		return parent;
	}
	return op;
}
