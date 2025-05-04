NAME	:=	minishell

CC		:=	cc

CFLAGS	:=	-Wall -Wextra -Werror -Isrc

VPATH	:=	src\
			src/enviroment\
			src/input\
			src/builtins

SRC 	:= 	env_delete_node.c\
			env_find_node.c\
			env_new_node.c\
			env_to_list.c\
			get_user_input.c\
			main_loop.c

GCTRL	:=	gctrl/garbage_control.c
LIBFT	:=	libft/libft.c

OBJ 	:=	$(SRC:.c=.o)

###

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(GCTRL) $(LIBFT)

clean:
	rm -f $(OBJ)
