void	env_delete_node(t_gctrl *gctrl, t_enviroment *list, t_enviroment *node)
{
	while (list->next != NULL && list->next != node)
		list = list->next;
	list->next = node->next;
	gctrl_free(gctrl, next->name);
	gctrl_free(gctrl, next->content);
	gctrl_free(gctrl, next->raw);
	gctrl_free(gctrl, next);
}
