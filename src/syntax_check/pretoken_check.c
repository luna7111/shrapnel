/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   pretoken_check.c                               .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/06/26 19:04:19 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/06/26 19:15:19 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	pretoken_check(t_pretoken *pretokens)
{
	while (pretokens->type != END)
	{
		if (pretokens->output_len > 0)
			return (1);
		pretokens++;
	}
	return (0);
}
