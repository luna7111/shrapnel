#include <minishell.h>

void	env_set_node(t_data *data, const char *name, const char *val)
{
	t_enviroment	*node;
	size_t			namelen;
	size_t			vallen;

	node = env_find_node(data->env, name);
	printf("Before: %s\n", node->raw);
	gctrl_free(data->gctrl, node->content);
	gctrl_free(data->gctrl, node->raw);
	node->content = ft_strdup(val);
	gctrl_track_ptr(data->gctrl, node->content, PROG_BLOCK);
	namelen = ft_strlen(name);
	vallen = ft_strlen(val);
	node->raw = gctrl_malloc(data->gctrl, PROG_BLOCK, namelen + vallen + 2);
	ft_memcpy(node->raw, node->name, namelen);
	node->raw[namelen] = '=';
	ft_memcpy(&node->raw[namelen + 1], node->content, vallen);
	node->raw[namelen + vallen + 1] = '\0';
	printf("After: %s\n", node->raw);
}
