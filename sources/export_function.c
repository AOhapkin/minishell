#include <stdbool.h>
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

void	export_function(t_list *arguments)
{
	int		args_count;

	args_count = ft_lstsize(arguments);
	if (args_count == 1)
		print_sorted_list(singleton->g_env);
	else
	{
		arguments = arguments->next;
		while(arguments)
		{
			//todo валидация строки (аргумента)
			if (!is_valid_export_arg(arguments->content))
				break;
			add_new_list_element(singleton->g_env, arguments->content);
			arguments = arguments->next;
		}
	}
}
