#include "minishell.h"

char *parse_lexeme_without_quote(char **value, char *buffer)
{
	char *from;
	char *to;

	if (ft_strchr(QUOTES, *buffer))
	{
		printf("начинается с кавычек");
		exit(1);
	}
	from = buffer;
	to = from;
	buffer++;
	while (buffer && *buffer && !ft_strchr(QUOTES, *buffer) && !ft_isspace(*buffer))
	{
		if (*buffer == ENV_CHAR)
		{
			if (to > from)
				*value = join_and_free_srcs(*value, ft_substr(from, 0, to - from));
			buffer = add_environment_value(value, ++buffer);
			from = buffer;
			to = buffer;
		}
		else
		{
			buffer++;
			to = buffer;
		}
	}
	if (to > from)
		*value = join_and_free_srcs(*value, ft_substr(from, 0, to - from));
	return buffer;
}

char *parse_lexeme_with_quote(char **value, char *buffer)
{
	char quote;
	char *from;
	char *to;

	if (!ft_strchr(QUOTES, *buffer))
	{
		printf("не начинается с кавычек");
		exit(1);
	}
	quote = *buffer;
	if (!ft_strchr(buffer + 1, quote))
		from = buffer;
	else
		from = buffer + 1;
	to = from;
	buffer++;
	while (buffer && *buffer && *buffer != quote)
	{
		if (*buffer == ENV_CHAR)
		{
			if (to > from)
				*value = join_and_free_srcs(*value, ft_substr(from, 0, to - from));
			buffer = add_environment_value(value, ++buffer);
			from = buffer;
			to = buffer;
		}
		else
		{
			buffer++;
			to = buffer;
		}
	}
	if (to > from)
		*value = join_and_free_srcs(*value, ft_substr(from, 0, to - from));
	if (*buffer)
		buffer++;
	return buffer;
}