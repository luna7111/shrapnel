#include <minishell.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*match;

	match = (unsigned char *)s;
	while (n--)
		if (*match++ == (unsigned char)c)
			return (match - 1);
	return (NULL);
}
