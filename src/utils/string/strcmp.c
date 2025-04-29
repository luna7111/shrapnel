/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcmp.c                                       .' .-'`        *          */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagro-r <nmagro-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:59:31 by nmagro-r          #+#    #+#             */
/*   Updated: 2025/04/28 01:51:12 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return(s1[i] - s2[i]);
}
// Returns the difference between the first different character netween two
// strings.
// First, checks if the two strings exist.
// Then iterates the two strings with i while the characters in the position
// i of both strings are the same and are not '\0'.
// returns the subs

/*
int main(void)
{
	printf("%d\n", ft_strcmp("b", "a")); // 1
	printf("%d\n", ft_strcmp("a", "a")); // 0
	printf("%d\n", ft_strcmp("aa", "ab")); // -1
	printf("%d\n", ft_strcmp("aa", "abb")); // -1
	printf("%d\n", ft_strcmp("0a", "")); // 48
	printf("%d\n", ft_strcmp(NULL, "a")); //segfault
}
*/
