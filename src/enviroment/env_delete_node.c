#include <minishell.h>

void	env_delete_node(t_gctrl *gctrl, t_enviroment **list, t_enviroment *node)
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
/*
int main(int argc, char **argv, char **env)
{
    t_gctrl         *gctrl;
    t_enviroment    *envlist;
    t_enviroment    *cursor;
    gctrl = gctrl_init();
    envlist = env_to_list(gctrl, env);
    cursor = envlist;
    while (cursor != NULL)
    {
        printf("...\n%s\n%s\n%s\n...\n", cursor->raw, cursor->name,
			cursor->content);
        cursor = cursor->next;
    }
    printf("\n00000000000000000000000000000000000000000000000000000000000\n");
    env_delete_node(gctrl, &envlist, env_find_node(envlist, "ZSH"));
    cursor = envlist;
    while (cursor != NULL)
    {
        printf("...\n%s\n%s\n%s\n...\n", cursor->raw, cursor->name,
			cursor->content);
        cursor = cursor->next;
    }
    gctrl_terminate(gctrl);
}*/
