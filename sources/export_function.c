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

int is_same_key_exist(char *argument)
{
	size_t len_for_compare;

	if (ft_strchr(argument, '='))
		len_for_compare = ft_strchr(argument, '=') - argument + 1;
	else
		len_for_compare = ft_strlen(argument);
	
	return 0;
}

//void	export_function(t_list *arguments)
//{
//	int		args_count;
//
//	args_count = ft_lstsize(arguments);
//	if (args_count == 1)
//		print_sorted_list(singleton->g_env);
//	else
//	{
//		arguments = arguments->next;
//		while(arguments)
//		{
//			//todo валидация строки и ошибка на экран
//			if (!is_valid_export_arg(arguments->content))
//			{
//				printf("Not valid arg - %s\n\n", (char *)arguments->content);
//				break;
//			}
//			if (is_same_key_exist(arguments->content))
//				find_and_replace(arguments->content);
//			else
//				add_new_list_element(singleton->g_env, arguments->content);
//			arguments = arguments->next;
//		}
//	}
//}

void add_or_update_the_parameter(t_list *env_list, char *export_arg)
{
	size_t len_for_compare;
	t_list *param;

	if (ft_strchr(export_arg, '='))
		len_for_compare = ft_strchr(export_arg, '=') - export_arg + 1;
	else
		len_for_compare = ft_strlen(export_arg);
	param = find_list_element_by_name(env_list, export_arg,
									  len_for_compare);
	if (param == NULL)
		add_new_list_element(singleton->g_env, export_arg);
	else
	{
		free(param->content);
		param->content = export_arg;
	}
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
			//todo валидация строки и ошибка на экран
			if (!is_valid_export_arg(arguments->content))
			{
				printf("Not valid arg - %s\n\n", (char *)arguments->content);
				break;
			}
			add_or_update_the_parameter(singleton->g_env, arguments->content);
			arguments = arguments->next;
		}
	}
}
