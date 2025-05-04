#include <minishell.h>

static t_data	*init_data(t_gctrl *gctrl, char **env)
{
	t_data	*data;

	data = gctrl_malloc(gctrl, sizeof(t_data), PROG_BLOCK);
	data->last_input = NULL;
	data->env = env_to_list(gctrl, env);
	return (data);
}

int	main(int argc, char **argv, char **env)
{
	t_gctrl	*gctrl;
	t_data	*data;
	t_iter	*iter_struct;

	gctrl = gctrl_init();
	data = init_data(gctrl, env);
	while (1)
	{
		iter_struct->raw_input = get_user_input(gctrl, data);
	}
	gctrl_terminate(gctrl);
	(void)argv;
	(void)argc;
}
