/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   get_user_input.c                               .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/04/25 18:40:17 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/04/27 16:43:03 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	input_has_content(char *input)
{
	while (*input == ' ')
		input++;
	return (*input != '\0');
}

static int	input_is_repeated(t_data *data, char *input)
{
	return (!ft_strcmp(data->))
}

static void	history_insertion(char *input)
{
	if (input_has_content(input) && !input_is_repeated(input))
		add_history(input);
}

char	*get_user_input(t_gctrl *gctrl, t_data *data)
{
	char	*input;
	
	input = readline("prompt placeholder> ");
	gctrl_track_ptr(gctrl, input, LOOP_BLOCK);
	history_insertion(input);
	return (input);
}

int main(void)
{
	t_gctrl	*gctrl;
	t_data	*data;

	gctrl = gctrl_init();

	while (strncmp(get_user_input(gctrl, data), "exit", 4))
		;
}
