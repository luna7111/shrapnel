/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   env_find_node.c                                .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/06/23 21:41:10 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/06/23 21:41:10 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_enviroment	*env_find_node(t_enviroment *head, const char *name)
{
	size_t	namelen;

	namelen = ft_strlen(name) + 1;
	while (head != NULL)
	{
		if (ft_strncmp(name, head->name, namelen) == 0)
			return (head);
		head = head->next;
	}
	return (NULL);
}
/*
int main(int argc, char **argv, char **env)
{
        t_gctrl                 *gctrl;
        t_enviroment    *envlist;

        gctrl = gctrl_init();
        envlist = env_to_list(gctrl, env);
		printf("%s\n", env_find_node(envlist, "ZSH")->content);
        gctrl_terminate(gctrl);
}
*/
