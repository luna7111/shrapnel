/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   minishell.h                                    .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/06/23 21:41:59 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/06/30 12:02:41 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

// printf, readline, perror:
# include <stdio.h>

// rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history:
# include <readline/history.h>
# include <readline/readline.h>

// exit, getenv:
# include <stdlib.h>

// write, acess, read, close, fork, getcwd, chdir, unlink, execve, dup, dup2,
// pipe, isatty, ttyname, ttyslot, tcsetattr, tcetattr:
# include <unistd.h>

// open, stat, lstat, fstat:
# include <fcntl.h>
# include <sys/stat.h>

// wait, waitpid, wait3, wait4:
# include <sys/wait.h>

// signal, sigaction:

# include <signal.h>

// opendir, readdir, closedir:
# include <dirent.h>
# include <sys/types.h>

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

//ioctrl
# include <termios.h>
# include <sys/ioctl.h>

////////////////////////////
//    Macros & enums    ////
////////////////////////////
// libft
# define BUFFER_SIZE 100
# define MAX_FD 1024

// garbage control block macros
# define PROG_BLOCK 1
# define LOOP_BLOCK 2

//pretoken types
# define END 0
# define TEXT 1
# define SYMBOL 2

extern int	g_exit_status;

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
}						t_enviroment;

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

 struct for the pretokens:

*/
typedef struct s_pretoken
{
	char	*str;
	int		type;
	size_t	input_len;
	size_t	output_len;
}	t_pretoken;

# define RE_END 0
# define RE_OK 1
# define RE_SKIP 2

typedef struct s_redir
{
	char	**cmd;
	int		flag;
	int		fd_in;
	int		fd_out;
}	t_redir;

typedef struct s_hdoc
{
	char	*content;
	int		fd;

}	t_hdoc;

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
}	t_token;

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
int				is_valid_number(char *str);
void			set_shlvl(t_data *data);
void			set_pwd(t_data *data);

// Enviroment management
t_enviroment	*env_new_node(t_gctrl *gctrl, const char *raw_variable);
t_enviroment	*env_find_node(t_enviroment *head, const char *name);
t_enviroment	*env_to_list(t_gctrl *gctrl, char **env);
void			env_add_node(t_data *data, const char *raw_var);
void			env_set_node(t_data *data, const char *name, const char *val);
void			env_set_raw(t_data *data, const char *raw_var);
void			env_delete_node(t_gctrl *g, t_enviroment **l, t_enviroment *n);
size_t			env_len(t_enviroment *env);

// Other functions
int				input_has_content(char *input);

// syntax_check
int				syntax_check(char *input);
int				pretoken_check(t_pretoken *pretokens);
int				token_check(t_token *tokens);
// Get input
char			*get_user_input(t_gctrl *gctrl, t_data *data);

// Expansion
char			*expand_input(t_data *data, char *str);
char			*expand_heredoc(t_data *data, char *str);

// Pretokenize
t_pretoken		*pretokenize_input(t_data *data, char *raw_input);

// Tokenize
t_token			*tokenize(t_data *data, t_pretoken *input);

// Redirect
t_redir			*redirect_tokens(t_data *data, t_token *tokens);

// Heredoc
char			*get_heredoc(t_data *data, t_token *token);

// Execute
void			execute(t_data *data, t_redir *exec_list);

// built-ins
int				ft_export(t_data *data, char **args);
int				ft_echo(char **args);
int				ft_cd(t_data *data, char **args);
int				ft_exit(t_data *data, char **args);
int				ft_unset(t_data *data, char **args);
int				ft_pwd(t_data *data);
int				ft_env(char **env);
int				shnake(void);

//signals
void			sigint_handler(int sig);
void			sigint_newline(int sig);
void			sigquit_handler(int sig);
void			set_handlers(void);
void			sigint_hdoc(int sig);

#endif
//              ,:/+/-
//              /M/              .,-=;//;-
//         .:/= ;MH/,    ,=/+%$XH@MM#@:
//        -$##@+$###@H@MMM#######H:.    -/H#
//   .,H@H@ X######@ -H#####@+-     -+H###@X
//    .,@##H;      +XM##M/,     =%@###@X;-
//  X%-  :M##########$.    .:%M###@%:
//  M##H,   +H@@@$/-.  ,;$M###@%,          -
//  M####M=,,---,.-%%H####M$:          ,+@##
//  @##################@/.         :%H##@$-
//  M###############H,         ;HM##M$=
//  #################.    .=$M##M$=
//  ################H..;XM##M$=          .:+
//  M###################@%=           =+@MH%
//  @#################M/.         =+H#X%=
//  =+M###############M,      ,/X#H+:,
//    .;XM###########H=   ,/X#H+:;
//       .=+HM#######M+/+HM@+=.
//           ,:/%XM####H/.
//                ,.:=-.
