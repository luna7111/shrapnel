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
