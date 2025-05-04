NAME	:=	minishell

CC		:=	cc

CFLAGS	:=	-Wall -Wextra -Werror -Isrc

VPATH	:=	src/enviroment src/input src/builtins

SRC 	:= 	env_delete_node.c\
			env_find_node.c\
			env_new_node.c\
			env_to_list.c\
			get_user_input.c\
			main_loop.c

OBJ 	:=	$(SRC:.c=.o)

###

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)
