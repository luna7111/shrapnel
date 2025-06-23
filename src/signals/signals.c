#include <minishell.h>

void sigint_handler(int sig)
{
    (void)sig;
    ioctl(1, TIOCSTI, "\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    g_exit_status = 130;
}
//Se activa cuando se pulsa Ctrl+C en el shell principal.
//Imprime un salto de línea para mantener el prompt limpio.
//Borra la línea actual de readline (rl_replace_line).
//Mueve el cursor a la línea nueva (rl_on_new_line).
//Redisplay para mostrar el prompt otra vez (rl_redisplay).
//Asigna el código de salida 130 (128 + número de SIGINT).

void    sigint_newline(int sig)
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
//Se usa en procesos hijo (ej. cat) para que al pulsar Ctrl+C 
//se imprima sólo un salto de línea.
//No hace más (el proceso termina automáticamente por SIGINT).

void	set_handlers(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

//Se activa con Ctrl+\ en shell interactivo.
//No termina el proceso, solo refresca el prompt.
//Código de salida 131 (128 + SIGQUIT).

void set_child_handlers(void)
{
    signal(SIGINT, sigint_newline);
    signal(SIGQUIT, SIG_DFL);
}
