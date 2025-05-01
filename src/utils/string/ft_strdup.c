#include <minishell.h>

char	*ft_strdup(const char *s)
{
	char	*duplicated_string;

	duplicated_string = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!duplicated_string)
		return (NULL);
	ft_strlcpy(duplicated_string, s, ft_strlen(s) + 1);
	return (duplicated_string);
}
