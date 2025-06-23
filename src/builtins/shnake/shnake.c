#include <minishell.h>
#include "shnake.h"

t_snake	*init_snake(void)
{
	t_snake	*snake;

	snake = malloc(sizeof(t_snake));
	snake->snake_len = 1;
	snake->body[0][X_POS] = 8;
	snake->body[0][Y_POS] = 8;
	snake->snake_direction = D_UP;
	snake->apple[X_POS] = 9;
	snake->apple[Y_POS] = 3;
	return (snake);
}

void	move_snake(t_snake *snake)
{
	int	snake_iterator;

	snake_iterator = snake->snake_len - 1;
	if (snake_iterator >= 64)
		snake_iterator = 63;
	while (snake_iterator > 0)
	{
		snake->body[snake_iterator][X_POS]
			= snake->body[snake_iterator - 1][X_POS];
		snake->body[snake_iterator][Y_POS]
			= snake->body[snake_iterator - 1][Y_POS];
		snake_iterator --;
	}
	if (snake->snake_direction == D_UP)
		snake->body[0][Y_POS]--;
	else if (snake->snake_direction == D_DOWN)
		snake->body[0][Y_POS]++;
	else if (snake->snake_direction == D_LEFT)
		snake->body[0][X_POS]--;
	else if (snake->snake_direction == D_RIGHT)
		snake->body[0][X_POS]++;
}

void	shnake_loop(t_snake *snake, unsigned long wait_time)
{
	while (g_exit_status == 0)
	{
		snake->snake_direction = get_head_direction(snake->snake_direction);
		move_snake(snake);
		if (snake->body[0][X_POS] == snake->apple[X_POS]
				&& snake->body[0][Y_POS] == snake->apple[Y_POS])
			eat_apple(snake);
		if (g_exit_status != 0)
			break ;
		print_map(snake);
		busy_wait(wait_time);
		wait_time -= wait_time / 250;
		if (check_death(snake))
			break ;
	}
}

#define FULLLINE "###################\n"
#define MIDLINE "#                 #\n"
#define EMPTYLINE "                   \n"

int	shnake(void)
{
	t_snake			*snake;
	unsigned long	wait_time;

	snake = init_snake();
	set_terminal_mode(1);
	wait_time = 200000000;
	signal(SIGINT, shnake_sigint_handler);
	signal(SIGQUIT, shnake_sigquit_handler);
	shnake_loop(snake, wait_time);
	printf(EMPTYLINE FULLLINE MIDLINE MIDLINE MIDLINE MIDLINE MIDLINE MIDLINE);
	printf("#   You lost! :(  #\n");
	printf("#    Score: %s%-3i%s   #\n", GREEN, snake->snake_len, RESET);
	printf(MIDLINE MIDLINE MIDLINE MIDLINE MIDLINE MIDLINE FULLLINE EMPTYLINE);
	set_terminal_mode(0);
	free(snake);
	set_handlers();
	g_exit_status = 0;
	return (0);
}
