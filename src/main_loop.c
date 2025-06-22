#include <minishell.h>

static t_data	*init_data(t_gctrl *gctrl, char **env)
{
	t_data	*data;

	data = gctrl_malloc(gctrl, PROG_BLOCK, sizeof(t_data));
	data->last_input = NULL;
	data->env = env_to_list(gctrl, env);
	data->last_exit_code = 69;
	return (data);
}

static t_iter	*init_iter(t_gctrl *gctrl)
{
	t_iter	*iter;

	iter = gctrl_malloc(gctrl, PROG_BLOCK, sizeof(t_data));
	iter->raw_input = NULL;
	return (iter);
}

void	print_pretokens(t_pretoken *pret)
{
	size_t	i;

	i = 0;
	while (pret[i].type != END)
	{
		printf("\n---\n%s\n%ld\n%ld\n%d\n---\n", pret[i].str, pret[i].input_len,
			pret[i].output_len, pret[i].type);
		i++;
	}
}

void	print_tokens(t_token *list)
{
	while (list)
	{
		printf("str: %-12s | type: %-2d | quoted: %d\n",
			list->str, list->type, list->quoted);
		list = list->next;
	}
	printf("---\n");
}

void	print_exec_list(t_redir *list)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (list[i].flag != RE_END)
	{
		j = 0;
		printf("\n---\n\nNode\n\n");
		if (list[i].flag == RE_SKIP)
			printf("(This node will be skiped by execution)\n\n");
		printf("Command args:\n");
		while (list[i].cmd[j])
		{
			printf("%s\n", list[i].cmd[j]);
			j++;
		}
		printf("\nfd in: %d\n", list[i].fd_in);
		if (list[i].fd_in > 2)
			close(list[i].fd_in);
		printf("fd out: %d\n", list[i].fd_out);
		if (list[i].fd_out > 2)
			close(list[i].fd_out);
		i++;
	}
}

int	g_exit_status = 0;

int	main(int argc, char **argv, char **env)
{
	t_gctrl	*gctrl;
	t_data	*data;
	t_iter	*iter;

	gctrl = gctrl_init();
	data = init_data(gctrl, env);
	data->gctrl = gctrl;
	iter = init_iter(gctrl);
	while (1)
	{
		set_handlers();
		iter->raw_input = get_user_input(data->gctrl, data);
		if (iter->raw_input == NULL)
			break ;
		if (input_has_content(iter->raw_input)
			&& syntax_check(iter->raw_input) == 1)
		{
			iter->pretokenized_input = pretokenize_input(data, iter->raw_input);
			iter->tokens = tokenize(data, iter->pretokenized_input);
			if (token_check(iter->tokens))
			{
				iter->exec_list = redirect_tokens(data, iter->tokens);
				execute(data, iter->exec_list);
			}
		}
		gctrl_cleanup(gctrl, LOOP_BLOCK);
	}
	gctrl_terminate(gctrl);
	(void)argv;
	(void)argc;
}
//the exit condition isn't the built in!!!
