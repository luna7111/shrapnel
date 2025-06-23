/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   shnake_ctrl.c                                  .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/06/23 21:37:34 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/06/23 21:37:35 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include "shnake.h"

void	shnake_sigint_handler(int sig)
{
	(void)sig;
	g_exit_status = 130;
}

void	shnake_sigquit_handler(int sig)
{
	(void)sig;
	g_exit_status = 131;
}

void	set_terminal_mode(int mode)
{
	static struct termios	oldt;
	static struct termios	newt;

	if (mode == 0)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	}
	else
	{
		tcgetattr(STDIN_FILENO, &oldt);
		newt = oldt;
		newt.c_lflag &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	}
}
