#include <minishell.h>

static t_data	*init_data(t_gctrl *gctrl, char **env)
{
	t_data	*data;

	data = gctrl_malloc(gctrl, PROG_BLOCK, sizeof(t_data));
	data->last_input = NULL;
	data->env = env_to_list(gctrl, env);
	return (data);
}

static t_iter	*init_iter(t_gctrl *gctrl)
{
	t_iter	*iter;

	iter = gctrl_malloc(gctrl, PROG_BLOCK, sizeof(t_data));
	iter->raw_input = NULL;
	return (iter);
}

int	main(int argc, char **argv, char **env)
{
	t_gctrl	*gctrl;
	t_data	*data;
	t_iter	*iter_struct;

	gctrl = gctrl_init();
	data = init_data(gctrl, env);
	iter_struct = init_iter(gctrl);
	while (1)
	{
		iter_struct->raw_input = get_user_input(gctrl, data);
		if (!ft_strcmp(iter_struct->raw_input, "exit"))
			break ;
	}
	gctrl_terminate(gctrl);
	(void)argv;
	(void)argc;
}
//the exit condition isn't the built in!!!
