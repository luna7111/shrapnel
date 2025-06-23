/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   cd_errors.c                                    .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/06/23 21:36:48 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/06/23 21:36:49 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include "cd_utils.h"

int	cd_error_too_many_args(void)
{
	ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	return (1);
}

//Function that prints an error if the user passes more than 1 argument to cd.
