/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   env_to_list.c                                  .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/06/23 21:41:41 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/06/23 21:41:42 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_enviroment	*env_to_list(t_gctrl *gctrl, char **env)
{
	t_enviroment	*head;
	t_enviroment	*new_node;

	head = NULL;
	while (*env != NULL)
	{
		new_node = env_new_node(gctrl, *env);
		new_node->next = head;
		head = new_node;
		env++;
	}
	return (head);
}
/*
int main(int argc, char **argv, char **env)
{
	t_gctrl			*gctrl;
	t_enviroment	*envlist;

	gctrl = gctrl_init();
	envlist = env_to_list(gctrl, env);
	while (envlist != NULL)
	{
		printf("...\n%s\n%s\n%s\n...\n", envlist->raw, envlist->name,
			envlist->content);
		envlist = envlist->next;
	}
	gctrl_terminate(gctrl);
}*/
