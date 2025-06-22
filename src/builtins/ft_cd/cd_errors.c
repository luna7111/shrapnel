#include <minishell.h>
#include "cd_utils.h"



int	cd_error_too_many_args(void)
{
	ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	return (1);
}
// Función que imprime un error si el usuario pasa más de un argumento a cd.