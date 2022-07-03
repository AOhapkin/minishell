/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmyriah <gmyriah@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:43:55 by gmyriah           #+#    #+#             */
/*   Updated: 2022/06/29 21:43:56 by gmyriah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1 != '\0' && *s2 != '\0')
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	init_singleton(char **envp)
{
	g_singleton = ft_memalloc(sizeof(t_glob));
	g_singleton->env = save_envp_to_list(envp);
	g_singleton->envp_chars = envp;
	g_singleton->last_exit_stat = 1;
	g_singleton->is_exit = FALSE;
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 1 && argv)
	{
		init_singleton(envp);
		routine();
		rl_clear_history();
		return (g_singleton->last_exit_stat);
	}
	exit (1);
}
