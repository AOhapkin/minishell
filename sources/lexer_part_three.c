#include "minishell.h"

/**
 * TODO узнать подробнее какие бывают ограничения на имена переменных
 * для bash shell
 */
int is_valid_for_env_var_name(char env_var_name_char)
{
	return ft_isalpha(env_var_name_char) || ft_isdigit(env_var_name_char) || env_var_name_char == '_';
}

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
	while (buffer && is_valid_for_env_var_name(*buffer))
		buffer++;
	return buffer;
}
