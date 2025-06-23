#include <minishell.h>

int	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] && ft_strchr(envp[i], '='))
		{
			write(1, envp[i], ft_strlen(envp[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	return (0);
}
// Function that prints out the environment variables received as arguments.
// It loops as long as there are environment variables (until NULL).
// Checks that the string is not empty and that it contains the character '='.
// Prints the complete environment variable to standard output and linefeed.
