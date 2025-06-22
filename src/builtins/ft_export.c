#include<minishell.h>
#include<stdlib.h>
#include<stdio.h>

void	export_set_or_append(t_data *data, const char *arg)
{
	char	*name;
	size_t	eq_sign;

	eq_sign = 0;
	while (arg[eq_sign] && arg[eq_sign] != '=')
		eq_sign++;
	name = ft_substr(arg, 0, eq_sign);
	if (env_find_node(data->env, name) == NULL)
		env_add_node(data, arg);
	else
	{
		if (ft_strchr(arg, '='))
			env_set_raw(data, arg);
		else
			env_set_node(data, arg, "");
	}
	free(name);
}
//Recibe una string tipo "VAR=value" o "VAR"
// - Si contiene '=', se pasa directamente a env_set_raw (que llama a env_set_node)
// - Si no contiene '=', se simula con "VAR=" para declararla sin valor

int	export_is_valid_key(const char *arg)
{
	int	i;

	if (!arg || !arg[0] || ft_isdigit(arg[0]) || arg[0] == '=')
		return (0);
	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
//Verifica que el nombre de la variable sea válido para exportar.
// - No debe comenzar con número ni ser vacío ni empezar con '='
// - Solo permite letras, números o '_', antes del '='

int	export_print_sorted(t_data *data)
{
	t_enviroment	*cur;

	cur = data->env;
	while (cur)
	{
		printf("declare -x %s=\"%s\"\n", cur->name, cur->content);
		cur = cur->next;
	}
	return (42);
}
// Imprime variables exportadas, usando copia del entorno actual.
// Formato: declare -x VAR="valor"

int	ft_export(t_data *data, char **args)
{
	int	i = 1;
	int	status = 0;

	if (!args[1])
	{
		printf("aaa\n");
		return (export_print_sorted(data));
	}
	while (args[i])
	{
		if (!export_is_valid_key(args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			status = 1;
		}
		else
			export_set_or_append(data, args[i]);
		i++;
	}
	return (status);
}
//Función principal del built-in export.
// - Sin argumentos: imprime el entorno ordenado
// - Con argumentos: los valida y exporta si son correctos
