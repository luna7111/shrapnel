#include <minishell.h>

static int is_n_flag(char *arg)
{
	int i;

	if(!arg || arg[0] != '-' || arg[1] != 'n')
		return(0);
	i = 2;
	while(arg[i])
	{
		if(arg[i] != 'n')
			return(0);
		i++;
	}
	return(1);
}

int	ft_echo(char **args)
{
	int i;
	int is_flaged;

	i = 1;
	is_flaged = 0;

	if(args[1])
	{
		while(args[i] && is_n_flag(args[i]))
		{
			is_flaged = 1;
			i++;
		}
		while(args[i])
		{
			write(1, args[i], ft_strlen(args[i]));
			if(args[i + 1])
				write(1, " ", 1);
			i++;
		}
		if(!is_flaged)
			write(1, "\n", 1);
		return(0);
	}
	return(0);

}

int main(int argc, char **argv)
{
	(void)argc;
	return ft_echo(argv);
}