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
//Función que imprime las variables de entorno recibidas como argumento.
//Itera mientras haya variables de entorno (hasta llegar a NULL).
//Verifica que el string no esté vacío y que contenga el carácter '='.
//Imprime la variable de entorno completa en la salida estándar y salto de línea
/*
int	main(void)
{
	char *env[] = 
	{
		"USER=student",
		"PWD=/home/student",
		"PATH=/usr/bin:/bin",
		"SHLVL=1",
		"EMPTYVAR",
		"TERM=xterm-256color",
		NULL
	};
	ft_env(env);

	return (0);
}
*/
