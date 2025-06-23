/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                   .' .-'`        *          */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagro-r <nmagro-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:43:56 by ldel-val          #+#    #+#             */
/*   Updated: 2025/06/22 23:57:53 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnchr(const char *s, int c, size_t len)
{
	while (*s && len > 0)
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *)s);
		s ++;
		len --;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}
