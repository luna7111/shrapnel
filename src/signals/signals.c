#include <minishell.h>

void sigint_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
    g_exit_status = 130;

//Se activa cuando se pulsa Ctrl+C en el shell principal.
//Imprime un salto de línea para mantener el prompt limpio.
//Borra la línea actual de readline (rl_replace_line).
//Mueve el cursor a la línea nueva (rl_on_new_line).
//Redisplay para mostrar el prompt otra vez (rl_redisplay).
//Asigna el código de salida 130 (128 + número de SIGINT).


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

void sigint_heredoc(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    close(STDIN_FILENO); // Forzar readline a devolver NULL
    g_exit_status = 130;
}
//Se llama cuando Ctrl+C se pulsa durante un heredoc (<<).
//Imprime un salto de línea.
//Cierra STDIN para forzar que readline() devuelva NULL y finalice el heredoc.
//Código de salida 130.


void    set_handlers(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigquit_handler);
}
//Registra los handlers del shell principal 
//(sigint_handler y sigquit_handler)

void set_heredoc_handler(void)
{
    signal(SIGINT, sigint_heredoc);
    signal(SIGQUIT, SIG_IGN);
}
//
void set_child_handlers(void)
{
    signal(SIGINT, sigint_newline);
    signal(SIGQUIT, SIG_DFL);
}
