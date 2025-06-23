/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   expand_aux.c                                   .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/06/23 21:39:20 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/06/23 21:39:21 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include "expand.h"

void	resize_array(t_data *data, t_chunk **array, size_t len, size_t new_len)
{
	t_chunk	*new;
	size_t	i;

	new = gctrl_malloc(data->gctrl, LOOP_BLOCK, new_len * sizeof(t_chunk));
	i = 0;
	while (i < len)
	{
		new[i] = *array[i];
		i++;
	}
	*array = new;
}

int	is_alpha_underscore(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int	is_alnum_underscore(char c)
{
	return (ft_isalnum(c) || c == '_');
}
