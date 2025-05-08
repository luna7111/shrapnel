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

// libft
# include "../libft/libft.h"

////////////////////////////
//    Macros & enums    ////
////////////////////////////
//libft
# define BUFFER_SIZE 100
# define MAX_FD 1024

//garbage control block macros
# define PROG_BLOCK 1
# define LOOP_BLOCK 2

///////////////////
//    Structs    //
///////////////////
/*

 struct for the nodes of the enviroment linked list

 char* raw:
	raw variable ej: "NAME=NACHETE"

 char* name:
	name of the variable ej: "NAME"

 char* content:
	content of the variable ej: "NACHETE"

*/
typedef struct s_enviroment
{
	char				*raw;
	char				*name;
	char				*content;
	struct s_enviroment	*next;
}	t_enviroment;

/*

 main struct with useful information for all the program:

 char*	last_input:
    the last input that was registered
    in the readline history, this is useful to avoid having the same
    input in the history two times in a row.

*/
typedef struct s_data
{
	t_gctrl			*gctrl;
	t_enviroment	*env;
	char			*last_input;
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
// Aux
// Enviroment management
t_enviroment	*env_new_node(t_gctrl *gctrl, const char *raw_variable);
t_enviroment	*env_find_node(t_enviroment *head, const char *name);
t_enviroment	*env_to_list(t_gctrl *gctrl, char **env);
void			env_delete_node(t_gctrl *g, t_enviroment **l, t_enviroment *n);
// Other functions
char			*get_user_input(t_gctrl *gctrl, t_data *data);
#endif
