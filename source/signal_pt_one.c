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

static void	handle_redir_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_singleton->last_exit_stat = 1;
		rl_replace_line(NULL, 0);
	}
	if (sig == SIGQUIT)
	{
		g_singleton->last_exit_stat = 131;
		printf("Quit: 3\n");
	}
}

void	handle_redir_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, handle_redir_signal);
}

int	termios_change(int echo_ctl_chr)
{
	struct termios	terminos_p;
	int				status;

	status = tcgetattr(STDOUT_FILENO, &terminos_p);
	if (status == -1)
		return (1);
	if (echo_ctl_chr)
		terminos_p.c_lflag |= ECHOCTL;
	else
		terminos_p.c_lflag &= ~(ECHOCTL);
	status = tcsetattr(STDOUT_FILENO, TCSANOW, &terminos_p);
	if (status == -1)
		return (1);
	return (0);
}
