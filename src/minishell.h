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

// types:
# include <stddef.h>

// memory management
# include "../gctrl/src/garbage_control.h"

// libft
# include "../libft/libft.h"

// types, macros
# include <stddef.h>

////////////////////////////
//    Macros & enums    ////
////////////////////////////
//libft
# define BUFFER_SIZE 100
# define MAX_FD 1024

//garbage control block macros
# define PROG_BLOCK 1
# define LOOP_BLOCK 2

//pretoken types
# define END 0
# define TEXT 1
# define SYMBOL 2

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
	int				last_exit_code;
}	t_data;

/*

 struct for the pretokens:

*/
typedef struct s_pretoken
{
	char	*str;
	int		type;
	size_t	input_len;
	size_t	output_len;
}	t_pretoken;

// FOR TESTING PURPOSES ONLY, THIS PIECE OF CODE DOESN'T BELONG IN THE MAIN
// BRANCH!!!!!!!!!!!!!!!!!!!!!!!
# define START 1
# define COMMAND 2
# define BUILTIN 3
# define PIPE 4
# define HEREDOC 5
# define DELIMITER 6
# define INFILE 7
# define OUTFILE 8
# define APPEND 9
# define FILENAME 10

typedef struct s_token
{
	char			*str;
	size_t			output_len;
	int				type;
	int				quoted;
	struct s_token	*next;
}	t_token;

#define RE_END 0
#define RE_OK 1
#define RE_SKIP 2

typedef struct s_redir
{
	char	**cmd;
	int		flag;
	int		fd_in;
	int		fd_out;
}	t_redir;

typedef struct	s_hdoc
{
	char	*content;
	int		fd;

} t_hdoc;
/*
	structs for tokens
*/

# define START 1
# define COMMAND 2
# define BUILTIN 3
# define PIPE 4
# define HEREDOC 5
# define DELIMITER 6
# define INFILE 7
# define OUTFILE 8
# define APPEND 9
# define FILENAME 10

typedef struct s_token
{
    char			*str;
	size_t			output_len;
    int				type;
	int				quoted;
	struct s_token	*next;
}   t_token;

/*

 struct with the information needed by each iteration of the loop:

	char* raw_input:
		the input received by readline, unprocessed.

	char* expanded_input:
		the input, with the env variables expended.
*/
typedef struct s_iter
{
	char		*raw_input;
	t_pretoken	*pretokenized_input;
	t_token		*tokens;
	t_redir		*exec_list;
}	t_iter;

///////////////////////////////
//    Function prototypes    //
///////////////////////////////
// Aux
// Enviroment management
t_enviroment	*env_new_node(t_gctrl *gctrl, const char *raw_variable);
t_enviroment	*env_find_node(t_enviroment *head, const char *name);
t_enviroment	*env_to_list(t_gctrl *gctrl, char **env);
void			env_add_node(t_data *data, const char *raw_var);
void			env_set_node(t_data *data, const char *name, const char *val);
void			env_set_raw(t_data *data, const char *raw_var);
void			env_delete_node(t_gctrl *g, t_enviroment **l, t_enviroment *n);
// Other functions
char			*get_user_input(t_gctrl *gctrl, t_data *data);

// syntax_check
int	syntax_check(char *input);

// Expansion
char			*expand_input(t_data *data, char *str);
char			*expand_heredoc(t_data *data, char *str);

//pretoken
t_pretoken		*pretokenize_input(t_data *data, char *raw_input);

//tokenize
t_token *tokenize(t_data *data, t_pretoken *input);

// built-ins
int	ft_echo(char **args);

char	*get_heredoc(t_data *data, t_token *token);

t_redir	*redirect_tokens(t_data *data, t_token *tokens);

#endif
