#include "minishell.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

char *get_input(void)
{
	char	*input;
	input = readline(PROMPT);
	if (input)
		add_history(input);
	return (input);
}

void	setup_terminal(void) {
	struct termios t;
	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

void while_true(void)
{
	char *buffer;
	int status;

	if (signal(SIGINT, handle_sigint) == SIG_ERR) {
		printf("failed to register interrupts with kernel\n");
	}
	setup_terminal();
	while (TRUE)
	{

//		signal(SIGQUIT, handle_sigquit);

		buffer = get_input();

		status = lexer(buffer);

		free(buffer);
	}
}