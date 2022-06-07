#include "minishell.h"

void	sort_array(char **array, int array_size)
{
	int		ordered;
	int		i;
	char	*tmp;

	ordered = 0;
	while (array && ordered == 0)
	{
		ordered = 1;
		i = 0;
		while (i < array_size - 1)
		{
			if (ft_strncmp(array[i], array[i + 1], strlen(array[i])) > 0)
			{
				tmp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tmp;
				ordered = 0;
			}
			i++;
		}
		array_size--;
	}
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	free(array);
}

void	print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("declare -x ");
		printf("%s\n", array[i]);
		i++;
	}
}
