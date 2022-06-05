#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <fcntl.h>
# include "libft.h"

# define PROMPT "minishell > "

# define TRUE 1
# define FALSE 0

# define DOUBLE_QUOTE '\"'
# define SINGLE_QUOTE '\''
# define QUOTES "\'\""
# define REDIRECTIONS_CHARS "<>|"
# define ENV_CHAR '$'

/**
 * Handler statuses
 */
# define SKIP 1
# define NOT_SKIP 0

/**
 * Commands
 */
# define ECHO_TYPE 1
# define EXEC_TYPE 2
# define NUM_OF_COMMANDS 2

/**
 * Flags
 */
# define ECHO_N_FLAG 21

/**
 * Args
 */
# define COMMAND_ARG_TYPE -1
# define REDIRECT_ARG_TYPE -2

/**
 * Redirections
 */
# define REDIRECT_OUTPUT 31 // >
# define APPENDING_REDIRECTED_OUTPUT 32 // >>
# define REDIRECT_INPUT 33 // <
# define HERE_DOCUMENTS 34 // <<

typedef struct s_token
{
	char *value;
	char type;
	struct s_token *next;
}				t_token;

t_token *new_token(char *first_char);
int get_size(t_token *head);
void free_list_of_tokens(t_token *head);
t_token *get_last_token(t_token *head);
t_token *pull_first_token(t_token **stack);
void push_token_back(t_token **stack, t_token *token);
void push_token_front(t_token **stack, t_token *token);
int get_position_in_the_stack(t_token *stack, t_token *token);
void print_all_tokens(t_token *token);

typedef struct s_lexer
{
	char *buffer;
	char *from;
	char *value;
	char quote;
	t_token *tokens;
} 				t_lexer;

t_token *lexer(char *buffer);
void lexer_init(t_lexer *lexer, char *buffer);
void lexer_update_value_and_quote(t_lexer *lexer, char quote);
void lexer_add_token(t_lexer *lexer);
void lexer_add_env_to_value_and_skip_name(t_lexer *lexer);
// handlers
int handle_quotes(t_lexer *lexer);
int handle_env_char(t_lexer *lexer);
int handle_redirect(t_lexer *lexer);
int handle_spaces(t_lexer *lexer);
int handle_simple_char(t_lexer *lexer);
int is_valid_char_for_env_var_name(char env_var_name_char);
char *join_and_free_srcs(char *s1, char *s2);
void expand_tokens(t_token *token);

typedef struct s_base
{
	t_token *command;
	t_token *input;
	int in;
	t_token *output;
	int out;
	int contain_args;
	int contain_flag;
	void (*function)(struct s_base*);
} 				t_base;
void echo_function(t_base *base);

void while_true(void);
char *read_from_input();
char *read_from_input_and_join_with_previous(char *prev);


int	open_out(t_base *base, t_token *token);



#endif
