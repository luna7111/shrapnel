#include <minishell.h>

void	env_delete_node(t_gctrl *gctrl, t_enviroment *list, t_enviroment *node)
{
	t_enviroment	*cursor;
	
	if (*list == node)
		*list = node->next;
	else
	{
		cursor = *list;
		while (cursor->next != node && cursor->next != NULL)
			cursor = cursor->next;
		cursor->next = node->next;
	}
	gctrl_free(gctrl, node->raw);
	gctrl_free(gctrl, node->name);
	gctrl_free(gctrl, node->content);
	gctrl_free(gctrl, node);
}
