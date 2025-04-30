#include <minishell.h>

char	*ft_strchr(char *str, char chr)
{
	while (*str)
	{
		if (*str == chr)
			return (str);
		str++;
	}
	if (*str == chr)
		return (str);
	return (NULL);
}
//function iterates the str pointer until it points to the null terminator '\0'
//of the string, if it finds the character (chr) it returns the pointer in that
//position. if not, it will return the pointer in the null terminator

//tests :
/*
int main()
{
	printf("1: %s\n", ft_strchr("Hola mundo que tal", 'a'));
	//"a mundo que tal\n"

	printf("2: %s\n", ft_strchr("Hola mundo que tal", 'H'));
	//"Hola mundo que tal\n"

	printf("3: %s\n", ft_strchr("", 'v'));
	//NULL

	printf("4: %s\n", ft_strchr("Hola mundo que tal", '\0'));
	//empty line

	printf("5: %s\n", ft_strchr("", '\0'));
	//empty line

	printf("6: %s\n", ft_strchr("hololo pipip", 'a'));
	//NULL

	printf("7: %s\n", ft_strchr(NULL, 'a'));
	//segfault
}*/
