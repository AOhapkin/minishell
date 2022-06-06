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

t_list *del_element_by_name(t_list *list, const char *name)
{
	t_list *temp = find_element_by_name(list, name);
	return NULL;
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
	// todo функция "добавить элемент"
	// todo принимает лист, возвращает сортированный массив по алфав
	elem = del_element_by_name(my_env, "USER");
	return (0);
}
