#include "minishell.h"


int	get_num_of_args(t_token *list_head)
{
	int		len;
	t_token	*tmp;

	tmp = list_head;
	len = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == COMMAND_ARG_TYPE || tmp->type == EXEC_TYPE)
			len++;
		tmp = tmp->next;
	}
	return (len);
}

char **get_argv(t_token *args_tokens)
{
	char	**args_array;
	int		array_len;
	int		i;

	array_len = get_num_of_args(args_tokens);
	args_array = ft_memalloc(sizeof(char *) * (array_len + 1));
	i = 0;
	while(args_tokens && args_tokens->type != PIPE)
	{
		if (args_tokens->type == COMMAND_ARG_TYPE
			|| args_tokens->type == EXEC_TYPE)
			args_array[i++] = args_tokens->value;
		args_tokens = args_tokens->next;
	}
	return (args_array);
}

void exec_function(t_op *op)
{
	char	*bin_path;
	char	**argv;

	bin_path = op->command->value;
	argv = get_argv(op->command);
	execve(bin_path, argv, singleton->envp_chars);
	free(argv);
}
