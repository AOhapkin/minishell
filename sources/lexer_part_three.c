#include "minishell.h"

char *join_and_free_srcs(char *s1, char *s2)
{
	char *result;

	if (!s1)
		result = s2;
	else if (!s2)
		result = s1;
	else
	{
		result = ft_strjoin(s1, s2);
		free(s1);
		free(s2);
	}
	return result;
}

char *add_environment_value(char **value, char *buffer)
{
	*value = join_and_free_srcs(*value, ft_strdup("ENV_VALUE"));
	while (buffer && *buffer && (ft_isalpha(*buffer) || ft_isdigit(*buffer)))
		buffer++;
	return buffer;
}
