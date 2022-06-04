#include "minishell.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

//char *get_input(void)
char *read_from_input_and_join_with_previous(char *previous_input)
{
	char	*input;

	input = readline(">");
	previous_input = join_and_free_srcs(previous_input, ft_strdup("\n"));
	input = join_and_free_srcs(previous_input, input);
	if (isatty(STDIN_FILENO) && input)
		add_history(input);
	return (input);
}

int is_all_quotes_close(char *input)
{
	char quote;

	quote = 0;
	while (*input)
	{
		if (ft_strchr(QUOTES, *input) && !quote)
			quote = *input;
		else if (ft_strchr(QUOTES, *input) && *input == quote)
			quote = 0;
		input++;
	}
	if (quote)
		return FALSE;
	else
		return TRUE;
}

char *read_from_input()
{
	char	*input;

	input = readline(PROMPT);
	while (!is_all_quotes_close(input))
		input = read_from_input_and_join_with_previous(input);
	if (isatty(STDIN_FILENO) && input)
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
	t_token *tokens;

	tokens = NULL;
	buffer = NULL;
	if (signal(SIGINT, handle_sigint) == SIG_ERR) {
		printf("failed to register interrupts with kernel\n");
	}
	setup_terminal();
	while (TRUE)
	{
		buffer = read_from_input();
		if (!buffer || ft_strlen(buffer) == 0)
			continue;
		tokens = lexer(buffer);
		expand_tokens(tokens);
//		print_all_tokens(tokens);
		free_list_of_tokens(tokens);
		free(buffer);
	}
}
