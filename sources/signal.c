#include "minishell.h"

static void	handle_cmd_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_singleton->last_exit_status = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	if (sig == SIGQUIT)
	{
		g_singleton->last_exit_status = 131;
		printf("Quit: 3\n");
	}
}

static void	handle_global_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_singleton->last_exit_status = 1;
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
