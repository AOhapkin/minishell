#include "minishell.h"

int	is_valid_env_char(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (TRUE);
	return (FALSE);
}

int	is_valid_export_arg(char *argument)
{
	int	i;

	i = 0;
	if (argument[i] == '\0' || argument[i] == '=')
		return (FALSE);
	while (argument[i] != '\0' && argument[i] != '=' && is_valid_env_char(argument[i]))
		i++;
	if (argument[i] == '=' || argument[i] == '\0')
		return (TRUE);
	return (FALSE);
}

void add_or_update_env_var(char *arg)
{
	t_list *current;
	t_env *new_env;
	char **separated;

	separated = ft_split(arg, '=');
	current = find_element_by_key(g_singleton->env, separated[0]);
	if (current == NULL)
	{
		new_env = new_env_by_key_value(separated[0], separated[1]);
		current = ft_lstnew(new_env);
		ft_lstadd_back(&(g_singleton->env), current);
	}
	else
	{
		free(((t_env*)(current->content))->value);
		((t_env*)(current->content))->value = separated[1];
		free(separated[0]);
	}
	free(separated);
}

void	export_function(t_op *op)
{
	t_token	*args;

	if (op->is_contain_args == FALSE)
		print_sorted_list(g_singleton->env);
	else
	{
		args = op->command->next;
		while(args && args->type != PIPE)
		{
			if (!is_valid_export_arg(args->value))
			{
				printf("Not valid arg - %s\n", (char *)args->value);
				break;
			}
			add_or_update_env_var(args->value);
			args = args->next;
		}
//		print_sorted_list(singleton->env); // оставил чтобы можно было проверить добавление
	}
	g_singleton->last_exit_status = 0;
}
