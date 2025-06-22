#include <minishell.h>

void    ctrl_minishell(int signal)
{
    if (signal == SIGINT)
    {
        write(1, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        g_exit_status = 130;
    }
    else if (signal == SIGQUIT)
    {
        rl_on_new_line();
        rl_redisplay();
        g_exit_status = 131;
    }
}
//Imprime un salto de línea (\n) para que el prompt no se mezcle con lo que había antes.
//Borra la línea actual de readline con rl_replace_line.
//Usa rl_on_new_line() para mover el cursor.
//Usa rl_redisplay() para mostrar el prompt limpio otra vez.
//Guarda g_exit_status = 130, que representa una interrupción por señal.
//Solo redibuja el prompt para ignorar visualmente la señal.
//Asigna g_exit_status = 131, que representa terminación con SIGQUIT.

void sigint_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
    g_exit_status = 130;
}

void sigquit_handler(int sig)
{
    (void)sig;
    rl_on_new_line();
    rl_redisplay();
    g_exit_status = 131;
}

void    set_handlers(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigquit_handler);
}