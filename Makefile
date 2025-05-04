NAME	:=	minishell

CC		:=	cc

CFLAGS	:=	-Wall -Wextra -Werror -Isrc -lreadline -fsanitize=address

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

GCTRL	:=	gctrl/garbage_control.a
LIBFT	:=	libft/libft.a

OBJ 	:=	$(SRC:.c=.o)

###

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(GCTRL) $(LIBFT)

clean:
	rm -f $(OBJ)
