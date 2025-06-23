#include <minishell.h>
#include "cd_utils.h"

int	cd_error_too_many_args(void)
{
	ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	return (1);
}

//Function that prints an error if the user passes more than 1 argument to cd.
