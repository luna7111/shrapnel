#include <minishell.h>

static int	input_has_content(char *input)
{
	while (*input == ' ')
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

char	*get_user_input(t_gctrl *gctrl, t_data *data)
{
	char	*input;

	input = readline("prompt placeholder> ");
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
