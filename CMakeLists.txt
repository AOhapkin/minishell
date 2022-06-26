cmake_minimum_required(VERSION 3.20)
project(minishell C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lreadline")

include_directories(libft/includes
        includes
        /opt/homebrew/Cellar/readline/8.1.2/include)

link_directories(/opt/homebrew/Cellar/readline/8.1.2/lib)

add_executable(minishell
        libft/includes/libft.h
        libft/sources/ft_atoi.c
        libft/sources/ft_bzero.c
        libft/sources/ft_calloc.c
        libft/sources/ft_isalnum.c
        libft/sources/ft_isalpha.c
        libft/sources/ft_isascii.c
        libft/sources/ft_isdigit.c
        libft/sources/ft_isnegative.c
        libft/sources/ft_isprint.c
        libft/sources/ft_isspace.c
        libft/sources/ft_itoa.c
        libft/sources/ft_lstadd_back.c
        libft/sources/ft_lstadd_front.c
        libft/sources/ft_lstclear.c
        libft/sources/ft_lstdelone.c
        libft/sources/ft_lstiter.c
        libft/sources/ft_lstlast.c
        libft/sources/ft_lstmap.c
        libft/sources/ft_lstnew.c
        libft/sources/ft_lstsize.c
        libft/sources/ft_memalloc.c
        libft/sources/ft_memchr.c
        libft/sources/ft_memcmp.c
        libft/sources/ft_memcpy.c
        libft/sources/ft_memmove.c
        libft/sources/ft_memset.c
        libft/sources/ft_newstr.c
        libft/sources/ft_putchar_fd.c
        libft/sources/ft_putendl_fd.c
        libft/sources/ft_putnbr_fd.c
        libft/sources/ft_putstr_fd.c
        libft/sources/ft_split.c
        libft/sources/ft_strchr.c
        libft/sources/ft_strdup.c
        libft/sources/ft_striteri.c
        libft/sources/ft_strjoin.c
        libft/sources/ft_strlcat.c
        libft/sources/ft_strlcpy.c
        libft/sources/ft_strlen.c
        libft/sources/ft_strmapi.c
        libft/sources/ft_strncmp.c
        libft/sources/ft_strnstr.c
        libft/sources/ft_strrchr.c
        libft/sources/ft_strtrim.c
        libft/sources/ft_substr.c
        libft/sources/ft_tolower.c
        libft/sources/ft_toupper.c
        sources/while_true.c
        sources/t_token_utils_part_one.c
        sources/t_token_utils_part_two.c
        sources/lexer.c
        sources/lexer_handlers.c
        sources/expander.c
        sources/echo_function.c
        sources/t_lexer_utils.c
        sources/redirection.c
        sources/interpreter.c
        sources/main.c
        sources/t_list_utils.c
        sources/array_utils.c
        sources/t_env_util.c
        sources/export_function.c
        sources/cd_function.c
        sources/unset_function.c
        sources/pwd_function.c
        sources/env_function.c
        sources/exit_function.c
        sources/redirections_handler.c
        sources/error_utils.c
        sources/exec_function.c)
