#include <minishell.h>

////variable global - 

void ft_sigint_handler(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay(); 
    g_exit_status = 130;               
}
//salta de línea para limpiar lo anterior.
//borra lo que el usuario estaba escribiendo.
//posiciona el cursor en la nueva línea.
//redibuja el prompt limpio.
//código de salida para Ctrl+C.

void ft_sigquit_handler(int sig)
{
    (void)sig;
}
// No hace nada en modo intreactivo.

////Ctrl + D en main_loop, readline()== NULL


void ft_sigint_heredoc(int sig)
{
	(void)sig;

}
//maneja ctrld dentro del heredoc