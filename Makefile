NAME = minishell

# libs
LIB_DIR = libft
LIB = $(LIB_DIR)/libft.a
INC_LIB = $(LIB_DIR)/includes
READLINE_LIB_DIR = /opt/homebrew/Cellar/readline/8.1.2/lib
READLINE_INC_DIR = /opt/homebrew/Cellar/readline/8.1.2/include

INC_MNSHL = includes

HEADER_MNSHL = $(INC_MNSHL)/minishell.h

# dirs
DIR_S = source
DIR_O = objects

# files
C_FILES = while_true.c\
		t_token_utils_part_one.c\
		t_token_utils_part_two.c\
		lexer.c\
		lexer_handlers_pt_one.c\
		lexer_handlers_pt_two.c\
		expander_pt_one.c\
		expander_pt_two.c\
		expander_pt_three.c\
		echo_function.c\
		t_lexer_utils.c\
		redirection.c\
		interpreter.c\
		main.c\
		t_list_utils_pt_two.c\
		t_list_utils_pt_one.c\
		array_utils.c\
		t_env_util.c\
		export_function.c\
		cd_function_pt_one.c\
		cd_function_pt_two.c\
		unset_function.c\
		pwd_function.c\
		env_function.c\
		exit_function.c\
		redirections_handler_pt_one.c\
		redirections_handler_pt_two.c\
		redirections_handler_pt_three.c\
		exec_function.c\
		signal_pt_one.c\
		signal_pt_two.c\

SRCS = $(addprefix $(DIR_S)/,$(C_FILES))
OBJS = $(addprefix $(DIR_O)/,$(C_FILES:.c=.o))

# flags
CC = gcc
FLAGS = -Wall -Werror -Wextra
INC_LIBS = -L $(LIB_DIR) -lft -L $(READLINE_LIB_DIR) -lreadline
INC_HEADERS = -I $(INC_MNSHL) -I $(INC_LIB) -I $(READLINE_INC_DIR)

.PHONY: all clean fclean re lib

all: $(NAME)

$(NAME): $(LIB) $(DIR_O) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(INC_LIBS) $(INC_HEADERS) -o $@

$(DIR_O):
	mkdir -p $(DIR_O)

$(LIB):
	make -C ./libft

$(DIR_O)/%.o: $(DIR_S)/%.c $(HEADER_MNSHL)
	$(CC) $(FLAGS) $(INC_HEADERS) -c ./$< -o $@

clean:
	rm -rf $(DIR_O)
	make -C ./libft fclean

fclean: clean
	rm -f $(NAME)

re: fclean all