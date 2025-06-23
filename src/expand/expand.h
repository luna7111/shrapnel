/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   expand.h                                       .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/06/23 21:39:14 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/06/23 21:39:16 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

typedef struct s_chunk
{
	char	*str;
	size_t	input_size;
}	t_chunk;

void	resize_array(t_data *data, t_chunk **array, size_t len, size_t new_len);
int		is_alpha_underscore(char c);
int		is_alnum_underscore(char c);

#endif
