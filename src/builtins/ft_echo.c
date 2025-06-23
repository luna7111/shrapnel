#include <minishell.h>

static int	is_n_flag(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
// checks if argument is an -n flag, allowing multiple n's (such as -nnn).
// If argument is null, does not start with -,
// or second character is not n, returns 0
// Starts iteration from the third character
// and runs through the rest of the string.
// If a character other than n is found, it is not a valid flag.
// All characters are n, valid flag -n is confirmed as valid flag -n.

int	ft_echo(char **args)
{
	int	i;
	int	is_flaged;

	i = 1;
	is_flaged = 0;
	if (args[1])
	{
		while (args[i] && is_n_flag(args[i]))
		{
			is_flaged = 1;
			i++;
		}
		while (args[i])
		{
			write(1, args[i], ft_strlen(args[i]));
			if (args[i + 1])
				write(1, " ", 1);
			i++;
		}
		if (!is_flaged)
			write(1, "\n", 1);
		return (0);
	}
	return (0);
}
// Function that simulates the echo command, with support for the -n flag.
// is_flaged = Flag to indicate whether the -n flag was detected.
// While there are -n flags, continues to advance.
// Marks that at least one -n flag was encountered.
// Recorrects the remaining arguments.
// Prints the current argument to standard output.
// If it is not the last argument, prints a space.
// If the -n flag was not used, adds a line break.
// If there are no arguments, prints nothing and returns 0.
