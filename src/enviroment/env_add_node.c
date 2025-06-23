/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   env_add_node.c                                 .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/06/23 21:40:56 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/06/23 21:40:57 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	env_add_node(t_data *data, const char *raw_var)
{
	t_enviroment	*node;

	node = env_new_node(data->gctrl, raw_var);
	node->next = data->env;
	data->env = node;
}
