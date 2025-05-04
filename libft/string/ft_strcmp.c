/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   ft_strcmp.c                                    .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2024/10/26 15:48:57 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/05/04 20:16:28 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
/*
int main()
{
	printf("%d\n", ft_strcmp("A", "Ab"));
}*/
