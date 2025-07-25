##########################################

NAME		:=	minishell

CC			:=	cc

CFLAGS		:=	-Wall -Wextra -Werror -Isrc

SRC 		:= 	src/enviroment/env_delete_node.c\
			src/enviroment/env_find_node.c\
			src/enviroment/env_new_node.c\
			src/enviroment/env_add_node.c\
			src/enviroment/env_to_list.c\
			src/enviroment/env_len.c\
			src/expand/expand_input.c\
			src/expand/expand_hdoc.c\
			src/expand/expand_aux.c\
			src/pretoken/pretoken_input.c\
			src/enviroment/env_set_node.c\
			src/enviroment/env_set_raw.c\
			src/execution/execute.c\
			src/execution/execute_aux.c\
			src/execution/execute_aux2.c\
			src/execution/execute_aux3.c\
			src/input/get_user_input.c\
			src/main_loop.c\
			src/aux.c\
			src/signals/signals.c\
			src/builtins/ft_echo.c\
			src/builtins/ft_pwd.c\
			src/builtins/ft_export.c\
			src/builtins/ft_unset.c\
			src/builtins/ft_exit.c\
			src/builtins/ft_env.c\
			src/builtins/ft_cd/cd_env_utils.c\
			src/builtins/ft_cd/cd_errors.c\
			src/builtins/ft_cd/cd_helpers.c\
			src/builtins/ft_cd/cd_target.c\
			src/builtins/ft_cd/ft_cd.c\
			src/builtins/shnake/shnake.c\
			src/builtins/shnake/shnake_aux.c\
			src/builtins/shnake/shnake_render.c\
			src/builtins/shnake/shnake_ctrl.c\
			src/heredoc/get_heredoc.c\
			src/redirect/redirect.c\
			src/redirect/redirect_aux.c\
			src/tokenize/tokenize.c\
			src/tokenize/tokenize_utils.c\
			src/syntax_check/token_check.c\
			src/syntax_check/pretoken_check.c\
			src/syntax_check/syntax_check.c

OBJ 		:=	$(SRC:.c=.o)

###########################################

GCTRL		:=	gctrl/garbage_control.a
GCTRLDIR	:=	gctrl

LIBFT		:=	libft/libft.a
LIBFTDIR	:=	libft

###########################################

all: $(NAME)

$(LIBFT):
	make -C $(LIBFTDIR)

$(GCTRL):
	make -C $(GCTRLDIR)

$(NAME): $(LIBFT) $(GCTRL) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(GCTRL) $(LIBFT) -lreadline 

clean:
	rm -f $(OBJ)
	make -C $(GCTRLDIR) fclean
	make -C $(LIBFTDIR) fclean

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
