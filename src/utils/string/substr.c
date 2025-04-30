/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagro-r <nmagro-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:58:38 by nmagro-r          #+#    #+#             */
/*   Updated: 2025/04/30 17:55:48 by nmagro-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_substr(char *str, unsigned int start, size_t len)
{
	char	*result;
	size_t	original_len;

	original_len = ft_strlen(str);
	if (!str || start >= original_len)
		return (NULL);
	if (len > original_len - start)
		len = original_len - start;
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	str += start;
	result[len] = '\0';
	while (len--)
		result[len] = str[len];
	return (result);
}
//Copies an substring starting at the position "start" and with a maximun
//lenght of "len":

//Check that str exists and start isnt bigger than the hole string
//If len would overflow the sting length, it is truncated to the max size 
//posible
//Allocates memory for the new string (len + 1) to account for the 
//'\0' terminator
//Checks if the malloc didn't fail
//Moves the pointer to the start position
//Adds '\0' terminator to the end of the string
//Iterates backwards copying each character from str to result :)


/*
int main(void)
{
	char	str[] = "Hola mundo! que tal?";
	printf("Original: %s\n", str);
	
	printf("Substr: %s\n", ft_substr(str, 0, 20));
	//"Hola mundo! que tal?"

	printf("Substr: %s\n", ft_substr(str, 1, 10));
	//"ola mundo!"
	
	printf("Substr: %s\n", ft_substr(str, 1, 100));
	//"ola mundo! que tal?" (acota len para que no se pase de largo)
	
	printf("Substr: %s\n", ft_substr(NULL, 1, 100)); //SEGFAULT
}*/
