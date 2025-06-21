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
