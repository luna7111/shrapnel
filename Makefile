##########################################

NAME		:=	minishell

CC			:=	cc

CFLAGS		:=	-Wall -Wextra -Werror -Isrc -fsanitize=address

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
			src/input/get_user_input.c\
			src/main_loop.c\
			src/builtins/ft_echo.c\
			src/heredoc/get_heredoc.c\
			src/redirect/redirect.c\
			src/redirect/redirect_aux.c\
			src/tokenize/tokenize.c\
			src/tokenize/tokenize_utils.c\
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
