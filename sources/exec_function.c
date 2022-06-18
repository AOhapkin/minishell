#include "minishell.h"


int	get_list_length(t_token *list_head)
{
	int		len;
	t_token	*temp;

	temp = list_head;
	len = 0;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}

char **save_list_values_to_array(t_token *list_head)
{
	char	**result_array;
	int		array_len;
	int		i;

	array_len = get_list_length(list_head);
//	result_array = malloc(sizeof(char *) * (array_len + 1));
//	ft_memset(result_array, NULL, array_len);
	result_array = ft_memalloc(array_len);
	ft_bzero(result_array, array_len);
	i = 0;
	while(list_head->value)
	{
		result_array[i] = ft_strdup(list_head->value);
		list_head = list_head->next;
	}
		result_array[i];
	return (result_array);
}

void exec_function(t_op *op)
{
	char	*file;
	char	**file_args;
	char	*args;
	char	*args2;

	printf("hello");
	file = op->command->value;
	file_args = save_list_values_to_array(op->command->next);
//	args = op->command->next->value;
//	args2 = op->command->next->next->value;
	printf("arg: %s\n", file);
	printf("arg: %s\n", *file_args);
//	printf("arg: %s\n", args2);

	execve(file, file_args, singleton->envp_chars);
}
