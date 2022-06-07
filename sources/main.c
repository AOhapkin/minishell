#include "minishell.h"
//
//int main(int argc, char **argv, char **envp)
//{
//
//	char *line;
//
//	while_true();
//	rl_clear_history();
//	return 0;
//}

t_list *find_element_by_name(t_list *list, const char *param_name)
{
	t_list	*elem;
	size_t name_len = ft_strlen(param_name);
	while (list)
	{
		if (ft_strncmp(list->content, param_name, ft_strlen(param_name)) == 0 && ((char*)list->content)[name_len] == '=')
		{
			elem = ft_lstnew(list->content);
			return elem;
		}
		list = list->next;
	}
	return NULL;
}

void	put_lst_content(void *content)
{
	printf("%s\n", (char *)content);
}

void	print_lst(t_list *list)
{
	ft_lstiter(list, put_lst_content);
}

// удаление, добавление и печать сортировки

void del_element_by_name(t_list *list, const char *param_name)
{
	t_list *temp;
	t_list *prev;
	size_t name_len;

	temp = list;
	prev = NULL;
	name_len = ft_strlen(param_name);
	while(temp)
	{
		prev = temp;
		temp = temp->next;
		if (ft_strncmp(temp->content, param_name, ft_strlen(param_name)) == 0 && ((char*)list->content)[name_len] == '=')
			break;
	}
	if (!temp)
		return ;
	prev->next = temp->next;
	free(temp);
}

void add_new_list_elem(t_list *list, const char *content)
{
	ft_lstadd_back(&list, ft_lstnew(ft_strdup(content)));
}

char	**list_to_array(t_list *lst)
{
	char	**env;
	int		i;
	int		lst_size = ft_lstsize(lst);

	if (!(env = malloc(sizeof(char *) * (lst_size + 1))))
		return (NULL);
	i = 0;
	while (lst)
	{
		env[i++] = (char *)(lst->content);
		lst = lst->next;
	}
	env[i] = NULL;
	return (env);
}

void	sort_env_array(char **array, int array_size)
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

void print_sorted_env_list(t_list *env)
{
	int	i;
	char	**env_array;
	char	*env_string;

	env_array = list_to_array(env);
	sort_env_array(env_array, ft_lstsize(env));
	i = 0;
	while (env_array[i])
	{
		printf("declare -x ");
		printf("%s\n", env_array[i]);
		i++;
	}
	free_array(env_array);
}

int main(int argc, char **argv, char **envp)
{
	t_list	*my_env;
	int	i;

	i = 0;
	my_env = ft_lstnew(ft_strdup(envp[i++]));
	while(envp[i])
	{
		ft_lstadd_back(&my_env, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
	print_lst(my_env);
	t_list *elem = find_element_by_name(my_env, "USER");
	printf("!!!!! %s\n", (char *)elem->content);
	elem = find_element_by_name(my_env, "PWD");
	printf("!!!!! %s\n", (char *)elem->content);
	// todo функция "удалить элемент по имени"
//	del_element_by_name(my_env, "USER");
//	print_lst(my_env);
	// todo функция "добавить элемент"
//	add_new_list_elem(my_env, "CONTENT");
	// todo принимает лист, возвращает сортированный массив по алфав
	print_sorted_env_list(my_env);
//	print_lst(my_env);
	return (0);
}
