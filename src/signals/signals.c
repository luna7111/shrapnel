#include <minishell.h>

void	sigint_handler(int sig)
{
	(void)sig;
	ioctl(1, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	g_exit_status = 130;
}
// Activated when Ctrl+C is pressed in the main shell.
// Print a line break to keep the prompt clean.
// Delete the current line of readline (rl_replace_line).
// Move the cursor to the new line (rl_on_new_line).
// Redisplay to show the prompt again (rl_redisplay).
// Assign the exit code 130 (128 + SIGINT number).

void	sigint_newline(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	sigquit_handler(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 131;
}
// Used in child processes (e.g. cat) so that when pressing Ctrl+C
// only one line break is printed.
// Does nothing else (the process is automatically terminated by SIGINT).
// Se usa en procesos hijo (ej. cat) para que al pulsar Ctrl+C

void	set_handlers(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

// Activate with Ctrl+ in interactive shell.
// Does not terminate the process, just refreshes the prompt.
// Exit code 131 (128 + SIGQUIT).

void	set_child_handlers(void)
{
	signal(SIGINT, sigint_newline);
	signal(SIGQUIT, SIG_DFL);
}
