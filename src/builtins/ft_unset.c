#include <minishell.h>

int	unset_is_valid_key(const char *arg)
{
	int	i;

	if (!arg || !arg[0] || ft_isdigit(arg[0]) || arg[0] == '=')
		return (0);
	i = 0;
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
// Reutiliza la lógica de validación de export,
// pero no permite que el nombre contenga '='.

void	unset_delete_var(t_data *data, const char *name)
{
	t_enviroment	*node;

	node = env_find_node(data->env, name);
	if (node)
		env_delete_node(data->gctrl, &data->env, node);
}
// Busca la variable en la lista y la elimina con env_delete_node.
// No imprime error si no existe, simplemente no hace nada.

int	ft_unset(t_data *data, char **args)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (args[i])
	{
		if (!unset_is_valid_key(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			status = 1;
		}
		else
			unset_delete_var(data, args[i]);
		i++;
	}
	return (status);
}
// Función principal del built-in unset.
// - Recorre cada argumento.
// - Si la clave es válida, la elimina si existe.
// - Si no es válida, imprime error.
