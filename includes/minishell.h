#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"
#include <readline/history.h>
#include <readline/readline.h>

# define PROMPT "minishell > "

//extern int is_reading;

char	*custom_readline(char *prompt);

#endif
