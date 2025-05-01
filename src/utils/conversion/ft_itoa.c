#include <minishell.h>

static int	ft_itob(int nb)
{
	int	byte_count;

	byte_count = 0;
	if (nb == 0)
		return (1);
	if (nb <= 0)
	{
		byte_count ++;
		nb *= -1;
	}
	while (nb)
	{
		byte_count ++;
		nb /= 10;
	}
	return (byte_count);
}

char	*ft_itoa(int n)
{
	char	*allocated_memory;
	int		size;

	size = ft_itob(n);
	allocated_memory = (char *)malloc(sizeof(char) * (size + 1));
	if (!allocated_memory)
		return (NULL);
	if (n == -2147483648)
		return (ft_memcpy(allocated_memory, "-2147483648", 12));
	allocated_memory[size] = '\0';
	if (n == 0)
		*allocated_memory = '0';
	if (n < 0)
	{
		allocated_memory[0] = '-';
		n *= -1;
	}
	while (n)
	{
		allocated_memory[size - 1] = (n % 10) + '0';
		n /= 10;
		size --;
	}
	return (allocated_memory);
}
