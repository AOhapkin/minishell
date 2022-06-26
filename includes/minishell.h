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
# define EXIT_TYPE 3
# define EXPORT_TYPE 4
# define ENV_TYPE 5
# define UNSET_TYPE 6
# define CD_TYPE 7
# define PWD_TYPE 8
# define NUM_OF_COMMANDS 8

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
# define PIPE 40 // |

typedef struct s_env
{
	char *key;
	char *value;
}				t_env;

void free_env(t_env **env);
void print_env(void *env);
t_env *new_env_by_key_value(char *key, char *value);
t_env *new_env_by_envp(char *string);

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

typedef struct s_base
{
	t_token *command;
	t_token *input;
	t_token *output;
	int is_contain_args;
	int is_contain_flag;
	struct s_base *child;
	void (*function)(struct s_base*);
 	int is_valid;
} 				t_op;

t_op *expand(t_token *token);
void handle_pipes(t_op *parent);
void interpreter(t_op *parent);

void echo_function(t_op *op);

void routine(void);
char *read_from_input();
char *read_from_input_and_join_with_previous(char *prev);


int	open_out(t_op *base, t_token *token);
int	open_in(t_op *base, t_token *token);

void	print_t_env_array(t_env **array);
void	sort_t_env_array(t_env **array, int array_size);

// Global struct

typedef struct s_glob
{
	t_list	*env;
	char	**envp_chars;
	int		last_exit_status;
	int		is_exit;
}	t_glob;

t_glob	*singleton;

t_list	*save_envp_to_list(char **envp);
t_list *find_element_by_key(t_list *list, char *key);
void	print_list_element_content(void *content);
void	print_list(t_list *list);
void	delete_list_element_by_name(t_list **list, const char *param_name);
t_env	**list_to_array(t_list *list);
void	print_sorted_list(t_list *list_head);

int		ft_strcmp(const char *s1, const char *s2);
void	export_function(t_op *op);
void	env_function(t_op *op);
void	unset_function(t_op *op);
void	pwd_function(t_op *op);
void	exec_function(t_op *op);
void	cd_function(t_op *operation);
void	exit_function(t_op *op);

void	handle_child_redirections(int fd[2], t_op *op);
void	handle_parent_redirections(int fd[2], t_op *op);

#endif
