/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagro-r <nmagro-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:59:31 by nmagro-r          #+#    #+#             */
/*   Updated: 2025/04/27 19:38:57 by nmagro-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (!s1 || !s2)
		return(-1);
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
	HACER PRUEBAS!!!!!!!!!!!!!!!!!!!!
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	printf("%d\n", ft_strcmp(NULL, "a"));
}
*/