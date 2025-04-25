/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   tinker_main_loop.c                             .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/04/25 16:14:06 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/04/25 17:35:47 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <unistd.h>

void	handler(int num)
{
	write(1, "\n", 1); //imprime un salto de linea
	rl_on_new_line(); //
	rl_replace_line("", 0);
	rl_redisplay();
}

int main(void)
{
	char *str;

	signal(SIGINT, handler);
	while (1)
	{
		str = readline("shrapnel> ");
		add_history(str);
		printf("%s\n", str);
		if (!strncmp("exit", str, 4))
			return (0);
	}
}
