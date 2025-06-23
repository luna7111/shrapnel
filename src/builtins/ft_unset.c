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
// Reuse the validation logic of export,
// but do not allow the name to contain '='.

void	unset_delete_var(t_data *data, const char *name)
{
	t_enviroment	*node;

	node = env_find_node(data->env, name);
	if (node)
		env_delete_node(data->gctrl, &data->env, node);
}
// Searches for the variable in the list and deletes it with env_delete_node.
// Doesn't print an error if it doesn't exist, it just does nothing.

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
// Main function of built-in unset.
// - Loops through each argument.
// - If the key is valid, removes it if it exists.
// - If invalid, prints error.