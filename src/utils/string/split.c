/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagro-r <nmagro-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:05:45 by nmagro-r          #+#    #+#             */
/*   Updated: 2025/04/30 16:54:40 by nmagro-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

static char	*copy_words(const char *s, int *i, char delim)
{
	char	*words;
	int		fin;

	while (s[*i] == delim)
		(*i)++;
	fin = *i;
	while (s[fin] != '\0' && s[fin] != delim)
		fin++;
	words = substr(s, *i, (fin - *i));
	*i = fin;
	return (words);
}
// Saltamos los delimitadores iniciales (espacios)
// Guardamos el inicio de la palabra
// Avanzamos hasta encontrar el siguiente delimitador o el final de la cadena
// Extraemos la palabra usando ft_substr desde *i hasta fin - *i
// Actualizamos *i para continuar después de esta palabra

static int	count_words(const char *str, char delim)
{
	int	count;
	int	i;

	count = 0;     
	i = 0;          
	while (str[i] != '\0')
	{
		if ((str[i] != delim) && (str[i + 1] == delim || str[i + 1] == '\0'))
		{
			count++; 
		}
		i++;  
	}
	return (count);  
}
// Inicializamos contador de palabras
// Empezamos desde el primer carácter de la cadena
// Recorremos la cadena completa
// Si el carácter actual no es el delimitador y el siguiente carácter es delimitador o fin de cadena,significa que encontramos el final de una palabra
// Contamos una palabra
// Avanzamos al siguiente carácter
// Devolvemos el total de palabras encontradas

static void	ft_free(char **ret, int j)
{
	while (j >= 0)
	{
		free(ret[j]);
		j--;
	}
	free(ret);
}
//Va liberando una por una las strings guardadas en ret desde la última posición usada (j) hacia la primera (0)
//Se hace hacia atrás porque si algo falla en ret[j], los anteriores ya fueron reservados correctamente

char	**ft_split(const char *s, char c)
{
	char	**ret;   // Array que almacenará los punteros a las palabras
	int		count;   // Número total de palabras que encontraremos
	int		j;       // Índice para recorrer el array 'ret'
	int		i;       // Índice para recorrer la string original 's'

	j = 0;          // Inicializamos el índice del array
	i = 0;          // Inicializamos el índice de recorrido de la cadena original

	count = count_words(s, c);
	ret = calloc(count + 1, sizeof(char *));
	if (ret == NULL)
		return (NULL);
	while (j < count)
	{
		ret[j] = copy_words(s, &i, c);
		if (ret[j] == NULL)
		{
			ft_free(ret, j);
			return (NULL);
		}
		j++; 
	}
	return (ret);
}
// Contamos cuántas palabras hay separadas por el delimitador 'c'
// Reservamos memoria para 'count' punteros a palabras, más 1 para el NULL final
// Si falla la reserva, retornamos NULL
// Iteramos mientras no hayamos copiado todas las palabras detectadas
// Copiamos la siguiente palabra desde 's' usando el índice actual 'i'
// Si hubo error al copiar la palabra, liberamos toda la memoria ya reservada
// Pasamos al siguiente slot del array
// Devolvemos el array de palabras terminado en NULL

int	main (void)
{
	const char *pepe ="hola que tal"; 
	char c = ' ';
	char **temp = ft_split(&pepe,c);
	int i = 0;
	while (temp[i] != NULL)
	{
		printf("%s\n",temp[i]);
		i++;
	}
	return (0);
}
