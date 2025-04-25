/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   minishell.h                                    .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/04/16 23:45:58 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/04/25 18:50:44 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// printf, readline, perror:
# include <stdio.h>

// rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history:
# include <readline/readline.h>
# include <readline/history.h>

// exit, getenv:
# include <stdlib.h>

// write, acess, read, close, fork, getcwd, chdir, unlink, execve, dup, dup2,
// pipe, isatty, ttyname, ttyslot, tcsetattr, tcetattr:
# include <unistd.h>

// open, stat, lstat, fstat:
# include <sys/stat.h>
# include <fcntl.h>

// wait, waitpid, wait3, wait4:
# include <sys/wait.h>

// signal, sigaction:
# include <signal.h>

// opendir, readdir, closedir:
# include <sys/types.h>
# include <dirent.h>

// strerror:
# include <string.h>

// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs:
# include <curses.h>
# include <term.h>

// errno:
# include <errno.h>

// memory management
# include "../garbage_control.h"

////////////////////////////
//    Macros & enums    ////
////////////////////////////
//garbage control block macros
# define LOOP_BLOCK 2

///////////////////////////////
//    Function prototypes    //
///////////////////////////////
// Aux functions
size_t	ft_strnlen(char *str);
char	*ft_strchr(char *str, char chr);
char	*ft_strrchr(char *str, char chr);

#endif
