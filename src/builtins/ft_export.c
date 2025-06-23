#include <minishell.h>

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
// Receives a string of type "VAR=value" or "VAR"
// - If it contains '=', it is passed directly
// to env_set_raw (which calls env_set_node)
// - If it does not contain '=', it is simulated with
//"VAR=" to declare it without value.

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
// Verify that the variable name is valid for export.
// - Must not start with a number or be empty or start with '='
// - Only allow letters, numbers or '_', before the '='.

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
// Print exported variables, using a copy of the current environment.
// Format: declare -x VAR="value".

int	ft_export(t_data *data, char **args)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
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
// Main function of built-in export.
// - Without arguments: prints the sorted environment
// - With arguments: validates and exports if correct