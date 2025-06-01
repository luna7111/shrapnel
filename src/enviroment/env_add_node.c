#include <minishell.h>

void	env_add_node(t_data *data, const char *raw_var)
{
	t_enviroment	*node;
	
	node = env_new_node(data->gctrl, raw_var);
	node->next = data->env;
	data->env = node;
}
