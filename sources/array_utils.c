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

void print_name_and_value(const char *string)
{
	char	*name;
	char	*value;

	printf("%s  ", string);


	if (ft_strchr(string, '='))
	{

	}
	else
	{
		printf("%s\n", string);
	}
//	printf("%s", name_value[0]);
//	if (ft_strchr(string, '='))
//	{
//		printf("=\"");
//		if (name_value[1])
//			printf("%s", name_value[1]);
//		printf("\"");
//	}
	printf("\n");


//	while (*name_value)
//	{
//		free(*name_value);
//		*name_value = NULL;
//		name_value++;
//	}
//	free(name_value);
//	name_value = NULL;
}


//void print_name_and_value(char *string)
//{
//	char	**name_value;
//
//	printf("%s\n", string);
//}



void	print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("declare -x ");
		print_name_and_value(array[i]);
		i++;
	}
}
