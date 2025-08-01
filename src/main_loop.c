/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   main_loop.c                                    .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/06/23 21:34:04 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/06/30 14:15:19 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_exit_status = 0;

static t_data	*init_data(t_gctrl *gctrl, char **env)
{
	t_data			*data;

	data = gctrl_malloc(gctrl, PROG_BLOCK, sizeof(t_data));
	data->last_input = NULL;
	data->env = env_to_list(gctrl, env);
	return (data);
}

static t_iter	*init_iter(t_gctrl *gctrl)
{
	t_iter	*iter;

	iter = gctrl_malloc(gctrl, PROG_BLOCK, sizeof(t_iter));
	iter->raw_input = NULL;
	return (iter);
}

int	main_loop(t_data *data, t_iter *iter)
{
	set_handlers();
	iter->raw_input = get_user_input(data->gctrl, data);
	if (iter->raw_input == NULL)
		return (0);
	if (input_has_content(iter->raw_input)
		&& syntax_check(iter->raw_input) == 1)
	{
		iter->pretokenized_input = pretokenize_input(data, iter->raw_input);
		iter->tokens = tokenize(data, iter->pretokenized_input);
		if (pretoken_check(iter->pretokenized_input)
			&& token_check(iter->tokens))
		{
			iter->exec_list = redirect_tokens(data, iter->tokens);
			if (g_exit_status != -1)
				execute(data, iter->exec_list);
			else
				g_exit_status = 0;
		}
	}
	gctrl_cleanup(data->gctrl, LOOP_BLOCK);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_gctrl	*gctrl;
	t_data	*data;
	t_iter	*iter;

	gctrl = gctrl_init();
	data = init_data(gctrl, env);
	data->gctrl = gctrl;
	iter = init_iter(gctrl);
	set_shlvl(data);
	set_pwd(data);
	g_exit_status = 0;
	while (1)
		if (main_loop(data, iter) == 0)
			break ;
	rl_clear_history();
	gctrl_terminate(gctrl);
	(void)argv;
	(void)argc;
}
//the exit condition isn't the built in!!!
