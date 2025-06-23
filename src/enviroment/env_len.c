/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   env_len.c                                      .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/06/23 21:41:19 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/06/23 21:41:20 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	env_len(t_enviroment *env)
{
	size_t	size;

	size = 0;
	while (env)
	{
		env = env->next;
		size ++;
	}
	return (size);
}
