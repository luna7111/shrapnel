#include <minishell.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	bytes;

	bytes = nmemb * size;
	if (size && nmemb > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(bytes);
	if (ptr == NULL)
		return (NULL);
	while(bytes-- > 0)
		((char *)ptr)[bytes] = 0;
	return (ptr);
}
//allocates memory and sets all bytes to 0

//checks if size * nmemb is bigger than SIZE_MAX
//allocates the memory
//checks the malloc worked fine (returns null if not)
//iterates thru the allocated memory backwards setting each byte to 0
//returns the pointer

/*
int main(void)
{
	char *str = ft_calloc(10, 10);
	int  i = 0;

	while (i < 90092)
	{
		printf("%d. %d\n", i, str[i]);
		i++;
	}
}*/