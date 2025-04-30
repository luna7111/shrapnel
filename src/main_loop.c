#include <minishell.h>

static t_data	*init_data(t_gctr *gctrl)
{
	t_data	*data;

	data = gctrl_malloc(gctrl, sizeof(t_data), PROG_BLOCK);
	data->last_input = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_gctrl	*gctrl;
	t_data	*data;
	t_iter	*iter_struct;

	gctrl = gctrl_innit();
	data = init_data(gctrl);
	while (1)
	{
		iter_struct->raw_input = get_user_input(gctrl, data);
	}
	gctrl_terminate(gctrl);
}
