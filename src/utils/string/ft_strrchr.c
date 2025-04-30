#include <minishell.h>

char	*ft_strrchr(char *str, char chr)
{
	char	*match;

	match = str;
	while (*match)
		match++;
	while (match > str)
	{
		if (*match == chr)
			return (match);
		match--;
	}
	if (*match == chr)
		return (match);
	return (NULL);
}
// Function creates a pointer, which iterates until the null terminator of the
// string, then iterates back until it finds the character or gets to the start
// if the character is found, it returns the pointer at that point of the string
// if not, it returns NULL
/*
int main()
{
	printf("1: %s\n", ft_strrchr("Hola Hola", 'H')); // "Hola\n"
	printf("2: %s\n", ft_strrchr("Hola mundo", 'o')); // "o\n"
	printf("3: %s\n", ft_strrchr("Hola mundo", 'p')); // NULL
	printf("4: %s\n", ft_strrchr("Hola mundo", '\0')); // Empty string
}
*/
