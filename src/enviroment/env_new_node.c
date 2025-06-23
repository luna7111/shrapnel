/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   env_new_node.c                                 .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/06/23 21:41:24 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/06/23 21:41:25 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_enviroment	*env_new_node(t_gctrl *gctrl, const char *raw_variable)
{
	t_enviroment	*node;
	int				eq_sign_position;

	eq_sign_position = ft_strchr(raw_variable, '=') - raw_variable;
	node = gctrl_malloc(gctrl, PROG_BLOCK, sizeof(t_enviroment));
	node->raw = ft_strdup(raw_variable);
	node->name = ft_substr(raw_variable, 0, eq_sign_position);
	node->content = ft_substr(raw_variable, eq_sign_position + 1,
			ft_strlen(raw_variable));
	node->next = NULL;
	gctrl_track_ptr(gctrl, node->raw, PROG_BLOCK);
	gctrl_track_ptr(gctrl, node->name, PROG_BLOCK);
	gctrl_track_ptr(gctrl, node->content, PROG_BLOCK);
	return (node);
}
/*
int main()
{
	t_gctrl	*gctrl;

	gctrl = gctrl_init();
	env_new_node(gctrl, "NAME=NACHETE");
	gctrl_terminate(gctrl);
}
*/
