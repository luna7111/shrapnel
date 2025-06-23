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
// Checks if the string is a valid number.
// - May optionally start with '+' or '-'
// - Must only contain trailing digits.

static int	exit_error_too_many_args(void)
{
	ft_putendl_fd("minishell: exit: too many arguments", 2);
	return (1);
}
// Handles the case of multiple invalid arguments to exit.
// Displays error and does NOT exit the program (Bash behaviour).

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
//Built-in exit: terminates the minishell.
//- If a numeric argument is passed: exits with that code.
//- If the argument is not numeric: error and exit with 255.
//- If there is more than one argument: error and no exit.