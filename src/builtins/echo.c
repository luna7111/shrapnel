#include <minishell.h>

static int num_args(char **args)
{
	int	size;
	
	size = 0;
	while(args[size])
		size++;
	return(size);
}
int	ft_echo(char **args)
{
	int i;
	int n_case;

	i = 1;
	n_case = 0;

	if(num_args(args) > 1)
	{
		while(args[i] && ft_strcmp(args[i], "-n") == 0)
		{
			n_case = 1;
			i++;
		}
		while(args[i])
		{
			write(1, args[i], ft_strlen(args[i]));
			if(args[i + 1])
				write(1, " ", 1);
			i++;
		}
		if(!n_case)
			write(1, "\n", 1);
		return(0);
	}
	return(0);

}
/*
int main(int argc, char **argv)
{
	(void)argc;
	return ft_echo(argv);
}
*/