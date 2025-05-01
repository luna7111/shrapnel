#include <minishell.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	size_t	string1_len;
	size_t	string2_len;

	if (!s1 || !s2)
		return (NULL);
	string1_len = ft_strlen(s1);
	string2_len = ft_strlen(s2);
	s = (char *)malloc(sizeof(char) * (string1_len + string2_len + 1));
	if (!s)
		return (NULL);
	ft_strlcpy(s, s1, string1_len + 1);
	ft_strlcat(s, s2, string1_len + string2_len + 1);
	return (s);
}
