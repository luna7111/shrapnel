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
//verifica si el argumento es un flag -n, permitiendo múltiples n (como -nnn).
//Si argumento es nulo,no empieza con -,o el segundo carácter no es n,retorna 0
//Inicia iteración desde el tercer carácter y recorre el resto del string.
//Si encuentra un carácter diferente de n, no es un flag válido.
//Todos los caracteres son n, se confirma como flag válido -n.

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
//Función que simula el comando echo, con soporte para el flag -n.
//is_flaged = Bandera para indicar si se detectó el flag -n.
//Mientras haya flags -n, continúa avanzando.
//Marca que se encontró al menos un flag -n.
//Recorre los argumentos restantes.
//Imprime el argumento actual a la salida estándar.
//Si no es el último argumento, imprime un espacio.
//Si no se usó el flag -n, añade un salto de línea.
//Si no hay argumentos, no imprime nada y retorna 0.
/*
int	main(int argc, char **argv)
{
	(void)argc;
	return (ft_echo(argv));
}
*/