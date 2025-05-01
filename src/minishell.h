/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmagro-r <nmagro-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 23:45:58 by ldel-val          #+#    #+#             */
/*   Updated: 2025/05/01 16:53:21 by nmagro-r         ###   ########.fr       */
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
typedef struct	s_data
{
	char	*last_input;
}	t_data;

///////////////////////////////
//    Function prototypes    //
///////////////////////////////
// Aux functions
size_t	ft_strlen(char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(char *str, char chr);
char	*ft_strrchr(char *str, char chr);
char	*ft_substr(char *str, unsigned int start, size_t len);
void	*ft_calloc(size_t nmemb, size_t size);

#endif
