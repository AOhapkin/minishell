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

int main(int argc, char **argv, char **envp)
{
	t_list *my_env;

	my_env = save_envp_to_list(envp);
	print_list(my_env);
	t_list *elem = find_list_element_by_name(my_env, "USER");
	printf("!!!!! %s\n", (char *)elem->content);
	elem = find_list_element_by_name(my_env, "PWD");
	printf("!!!!! %s\n", (char *)elem->content);
//	del_element_by_name(my_env, "USER");
//	print_lst(my_env);
//	add_new_list_elem(my_env, "CONTENT");
	print_sorted_list(my_env);
//	print_lst(my_env);
	return (0);
}

// todo разнести на файлы

// todo поиск и запуск бинарника

// todo обработка ошибок

// todo удаление единственного элемента листа