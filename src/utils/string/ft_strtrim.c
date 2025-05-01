#include "../libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		start;
	size_t		end;

	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start ++;
	end = ft_strlen(s1) - 1;
	while (end && ft_strchr(set, s1[end]))
		end --;
	if (end < start)
		return (ft_calloc(1, sizeof(char)));
	return (ft_substr(s1, start, end - start + 1));
}
