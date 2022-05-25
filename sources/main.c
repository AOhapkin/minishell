#include "minishell.h"

int main(int argc, char **argv, char **envp)
{

    char	*line;

    line = readline(PROMPT);
    return 0;
}