#include <minishell.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>

static int	cd_error_too_many_args(void)
{
	ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	return (1);
}
// Función auxiliar que imprime un error si el usuario pasa más de un argumento a cd.