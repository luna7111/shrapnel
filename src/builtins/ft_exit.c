#include <minishell.h>

static int	is_numeric_arg(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
// Verifica si el string es un número válido.
// - Opcionalmente puede empezar con '+' o '-'
// - Solo debe contener dígitos después.

static int	exit_error_too_many_args(void)
{
	ft_putendl_fd("minishell: exit: too many arguments", 2);
	return (1);
}
// Maneja el caso de múltiples argumentos inválidos para exit.
// Muestra error y NO sale del programa (comportamiento Bash).

int	ft_exit(t_data *data, char **args)
{
	int	code;

	code = 0;
	ft_putendl_fd("exit", STDOUT);
	if (args[1])
	{
		if (!is_numeric_arg(args[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit(255);
		}
		if (args[2])
			return (exit_error_too_many_args());
		code = ft_atoi(args[1]);
	}
	gctrl_terminate(data->gctrl);
	exit(code);
}
//Built-in exit: termina el minishell.
//- Si se pasa un argumento numérico: sale con ese código.
//- Si el argumento no es numérico: error y sale con 255.
//- Si hay más de un argumento: muestra error y no sale.
