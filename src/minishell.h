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
typedef struct	s_enviroment
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
//
// Aux functions
//
// String
char	**ft_split(char *s, char c);
char	*ft_strchr(char *str, char chr);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(char *str);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(char *str, char chr);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char *str, unsigned int start, size_t len);

// Memory
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);

// IO
int		ft_dprintf(int fd, char const *format, ...);
char	*get_next_line(int fd);

// Conversion
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);

// Other functions
char	*get_user_input(t_gctrl *gctrl, t_data *data);
#endif
