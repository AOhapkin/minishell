/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmyriah <gmyriah@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 21:44:12 by gmyriah           #+#    #+#             */
/*   Updated: 2022/06/29 21:44:13 by gmyriah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_cmd_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_singleton->last_exit_stat = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	if (sig == SIGQUIT)
	{
		g_singleton->last_exit_stat = 131;
		printf("Quit: 3\n");
	}
}

static void	handle_global_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_singleton->last_exit_stat = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_cmd_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGQUIT, handle_cmd_signal);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, handle_cmd_signal);
}

void	handle_global_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, handle_global_signal);
}
