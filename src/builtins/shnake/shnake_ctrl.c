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
