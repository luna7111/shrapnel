# **************************************************************************** #
#                                                                              #
#                                                     _.._  .           .      #
#    Makefile                                       .' .-'`        *           #
#                                                  /  /       +        *       #
#    By: ldel-val <ldel-val@student.42madrid.com>  |  |           *            #
#                                                  \  '.___.;       +          #
#    Created: 2025/04/16 13:53:42 by ldel-val       '._  _.'   .        .      #
#    Updated: 2025/04/16 15:58:58 by ldel-val          ``                      #
#                                                                              #
# **************************************************************************** #

CC			:= cc
CFLAGS		:= -lreadline -g3 -Ilib/gctrl/src
RM			:= rm -f

GCTRL		:= lib/gctrl/garbage_control.a
GCTRL_DIR	:= lib/gctrl

$(GCTRL):
	$(MAKE) -C $(GCTRL_DIR)

tinker_gctrl_env_linked_list: $(GCTRL) src/tinker_gctrl_env_linked_list.c
	$(CC) $(CFLAGS) src/tinker_gctrl_env_linked_list.c $(GCTRL) -o tinker_gctrl_env_linked_list
