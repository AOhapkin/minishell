#include "minishell.h"

t_list	*save_envp_to_list(char **envp)
{
	t_list	*new_list;
	int		i;

	i = 0;
	new_list = ft_lstnew(ft_strdup(envp[i++]));
	while(envp[i])
	{
		ft_lstadd_back(&new_list, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
	return (new_list);
}

t_list *find_list_element_by_name(t_list *list, const char *param_name)
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

void	print_list_element_content(void *content)
{
	printf("%s\n", (char *)content);
}

void	print_list(t_list *list)
{
	ft_lstiter(list, print_list_element_content);
}

void	delete_list_element_by_name(t_list *list, const char *param_name)
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

void	add_new_list_element(t_list *list, const char *content)
{
	ft_lstadd_back(&list, ft_lstnew(ft_strdup(content)));
}

char	**save_list_values_to_array(t_list *lst)
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

void	print_sorted_list(t_list *list_head)
{
	int	i;
	char	**values_array;

	values_array = save_list_values_to_array(list_head);
	sort_array(values_array, ft_lstsize(list_head));
	print_array(values_array);
	free_array(values_array);
}

