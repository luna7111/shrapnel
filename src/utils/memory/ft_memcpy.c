#include "../libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	while (n)
	{
		((char *)dest)[n - 1] = ((char *)src)[n - 1];
		n--;
	}
	return (dest);
}
