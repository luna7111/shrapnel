/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   tinker_gctrl_env_linked_list.c                 .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/04/16 11:20:22 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/04/16 23:21:07 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <garbage_control.h>
#include <stdio.h>

typedef struct s_env
{
	char *name;
	char *val;
	struct s_env *next;
}	t_env;

t_env	*add_env_node(t_gctrl *gctrl, char *str)
{
	t_env	*node;
	char	*content_start;

	content_start = str;
	while (*content_start != '=')
		content_start ++;

	return (node);
}

int main(int argc, char **argv, char **env)
{
	t_gctrl *gctrl;
	t_env	*env_list;

	gctrl = gctrl_init();
	env_list = add_env_node(gctrl, "Before the eq=after the eq");
	printf("%s\n", env_list->name);
	gctrl_terminate(gctrl);
}
