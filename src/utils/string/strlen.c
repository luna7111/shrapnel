#include <minishell.h>

size_t	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (*str)
	{
		str++;
		len++;
	}
	return (len);
}
// iterates using the str pointer until it points to a null terminator ('\0'),
// in each step adds one to len. when the pointer reaches the null terminator
// the function returns len
/* Tests:
int main()
{
	printf("1: %ld\n", ft_strlen("Hola")); //4
	printf("2: %ld\n", ft_strlen("")); //0
	printf("3: %ld\n", ft_strlen("p")); //1
	printf("4: %ld\n", ft_strlen(NULL)); //segfault
}*/
