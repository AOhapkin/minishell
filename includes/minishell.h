#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"
#include <readline/history.h>
#include <readline/readline.h>

# define PROMPT "minishell > "

# define TRUE 1
# define FALSE 0

# define WHITESPACE_CHARS " \t\r\v\f\n"
# define DOUBLE_QUOTE '\"'
# define SINGLE_QUOTE '\''
# define QUOTES "\'\""
# define NOT_INTERPRET_CHARS "\\;$"

/**
 * Three token types
 */
# define COMMAND 'c' //ex
# define ARGUMENT 'a'
# define FLAG 'f'
# define OPERATOR 'o' // <,>,<<,>>,|

/**
 * COMMANDs and FLAGSs
 */
# define ECHO "echo"
# define ECHO_N_FLAG "-n" // no '\n' at the end
# define CD "cd" // with relative or absolute path
# define PWD "pwd" // with no options
# define EXPORT "export" // with no options
# define UNSET "unset" // with no options
# define ENV "env" // with no options or arguments
# define EXIT "exit" // with no options

/**
 * OPERATORs
 */
# define EXECUTE "./"

/**
 * Three token types
 */
# define COMMAND 'c' //ex
# define ARGUMENT 'a'
# define FLAG 'f'
# define OPERATOR 'o' // <,>,<<,>>,|,/
# define ENV_CHAR '$'

typedef struct s_lexer
{
	char *start;
	char *finish;
	char quote;
} 				t_lexer;

typedef struct s_token
{
	char *value;
	char type;
	struct s_token *next;
}				t_token;

void while_true(void);

int lexer(char *buffer);
t_token *get_new_token(char **buffer);
int is_valid_char_for_env_var_name(char env_var_name_char);

t_token *new_token(char *first_char);
int get_size(t_token *head);
void free_list_of_tokens(t_token *head);
t_token *get_last_token(t_token *head);
t_token *pull_first_token(t_token **stack);
void push_token_back(t_token **stack, t_token *token);
void push_token_front(t_token **stack, t_token *token);
int get_position_in_the_stack(t_token *stack, t_token *token);

char *join_and_free_srcs(char *s1, char *s2);

#endif
