#include <minishell.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*casted_string1;
	unsigned char	*casted_string2;

	casted_string1 = (unsigned char *)s1;
	casted_string2 = (unsigned char *)s2;
	while (n)
	{
		if (*casted_string1 != *casted_string2)
			return (*casted_string1 - *casted_string2);
		casted_string1 ++;
		casted_string2 ++;
		n--;
	}
	return (0);
}
