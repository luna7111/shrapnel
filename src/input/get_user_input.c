/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   get_user_input.c                               .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/06/23 21:38:02 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/06/29 19:16:52 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	input_has_content(char *input)
{
	if (input == NULL)
		return (0);
	while (*input == ' ' || *input == '"' || *input == '\'')
		input++;
	return (*input != '\0');
}
//Skips all the spaces in the input, returns the inverse of input == '\0'
//so if there is anything else than a space, function returns 1 and if not,
//returns 0

static int	input_is_repeated(t_data *data, char *input)
{
	if (data->last_input == NULL)
		return (0);
	return (!ft_strcmp(data->last_input, input));
}
//last_input is a variable in the data struct which contains the input of the
//last iteration, if input and data->last_input are the same, returns 1
//, if they are different

static void	history_insertion(t_gctrl *gctrl, t_data *data, char *input)
{
	if (input_has_content(input) && !input_is_repeated(data, input))
	{
		add_history(input);
		if (data->last_input != NULL)
			gctrl_free(gctrl, data->last_input);
		data->last_input = input;
	}
}
//checks if the input is valid (has content and isn't the same as the previous)
//entry. if so, adds the input to history and changes data->last_input to the
//current entry

#define MAGENTA "\001\x1B[35m\002"
#define RESET "\001\x1B[0m\002"

char	*get_user_input(t_gctrl *gctrl, t_data *data)
{
	char			*input;
	char			*prompt;
	t_enviroment	*user;

	user = env_find_node(data->env, "USER");
	if (user == NULL)
		prompt = ft_strjoin(MAGENTA, "shrapnel > "RESET);
	else
	{
		prompt = ft_strjoin(user->content, "@shrapnel > "RESET);
		gctrl_track_ptr(data->gctrl, prompt, LOOP_BLOCK);
		prompt = ft_strjoin(MAGENTA, prompt);
	}
	gctrl_track_ptr(data->gctrl, prompt, LOOP_BLOCK);
	input = readline(prompt);
	gctrl_track_ptr(gctrl, input, PROG_BLOCK);
	history_insertion(gctrl, data, input);
	return (input);
}
//calls readline and stores the result in the input variable. tracks the string
//pointer to avoid leaks, calls history insertion to manage whether the input
//should be registered in history or not
/*
int main(void)
{
	t_gctrl	*gctrl;
	t_data	*data;
	char	*input;

	gctrl = gctrl_init();
	data = gctrl_malloc(gctrl, PROG_BLOCK, sizeof(t_data));
	data->last_input = NULL;
	input = get_user_input(gctrl, data);
	printf("%s\n", input);
	while (ft_strcmp("exit", input))
	{
		input = get_user_input(gctrl, data);
		printf("%s\n", input);
	}
	gctrl_terminate(gctrl);
}*/
