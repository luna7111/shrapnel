/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   minishell.h                                    .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/04/16 23:45:58 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/04/30 12:38:21 by ldel-val          ``                     */
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
# include "../gctrl/src/garbage_control.h"

////////////////////////////
//    Macros & enums    ////
////////////////////////////
//garbage control block macros
# define PROG_BLOCK 1
# define LOOP_BLOCK 2

///////////////////
//    Structs    //
///////////////////
/*

 main struct with useful information for all the program:

 char*	last_input:
    the last input that was registered
    in the readline history, this is useful to avoid having the same
    input in the history two times in a row.

*/
typedef struct s_data
{
	char	*last_input;
}	t_data;

/*

 struct with the information needed by each iteration of the loop:

	char* raw_input:
		the input received by readline, unprocessed.

	char* expanded_input:
		the input, with the env variables expended.
*/
typedef struct s_iter
{
	char	*raw_input;
	char	*expanded_input;
}	t_iter;

///////////////////////////////
//    Function prototypes    //
///////////////////////////////
// Aux functions
size_t	ft_strlen(char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(char *str, char chr);
char	*ft_strrchr(char *str, char chr);

// Other functions
char	*get_user_input(t_gctrl *gctrl, t_data *data);
#endif
