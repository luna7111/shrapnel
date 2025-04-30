/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagro-r <nmagro-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:58:38 by nmagro-r          #+#    #+#             */
/*   Updated: 2025/04/30 17:25:07 by nmagro-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*result;

	if (!str)
		return (NULL);
	result = malloc((len + 1) * sizeof(char));
	str += start;
	result[len] = '\0';
	while (len--)
		result[len] = str[len];
	return(result);
}

int main(void)
{
	char	str[] = "Hola mundo! que tal?";
	printf("Original: %s\n", str);
	printf("Substr: %s\n", ft_substr(str, 1, 10));
}