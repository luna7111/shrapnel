/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   shnake_aux.c                                   .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/06/23 21:37:22 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/06/23 21:37:25 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include "shnake.h"

int	get_head_direction(int current)
{
	char	buf[128];
	int		n;

	ioctl(STDIN_FILENO, FIONREAD, &n);
	if (n <= 0)
		return (current);
	n = read(STDIN_FILENO, buf, 128);
	if (n >= 3 && buf[0] == 27 && buf[1] == 91)
	{
		if (buf[2] == 65 && current != D_DOWN)
			return (D_UP);
		else if (buf[2] == 66 && current != D_UP)
			return (D_DOWN);
		else if (buf[2] == 67 && current != D_LEFT)
			return (D_RIGHT);
		else if (buf[2] == 68 && current != D_RIGHT)
			return (D_LEFT);
	}
	return (current);
}

void	busy_wait(unsigned long int units)
{
	volatile unsigned long int	i;

	i = 0;
	while (i < units)
		i++;
	return ;
}

int	pseudo_random_number(t_snake *snake)
{
	static int	number = 3;

	number += (long)snake % 18;
	number += snake->apple[X_POS] + snake->body[0][Y_POS] + 3;
	number *= 13;
	number = number % 16;
	return (number);
}

void	eat_apple(t_snake *snake)
{
	if (snake->snake_len < 64)
	{
		snake->body[snake->snake_len][Y_POS] = -1;
		snake->body[snake->snake_len][X_POS] = -1;
	}
	snake->snake_len ++;
	snake->apple[X_POS] = pseudo_random_number(snake);
	snake->apple[Y_POS] = pseudo_random_number(snake);
}

int	check_death(t_snake *snake)
{
	int	i;

	i = snake->snake_len - 1;
	while (i > 0)
	{
		if (snake->body[0][X_POS] == snake->body[i][X_POS])
			if (snake->body[0][Y_POS] == snake->body[i][Y_POS])
				return (1);
		i--;
	}
	if (snake->body[0][X_POS] >= 16 || snake->body[0][X_POS] < 0)
		return (1);
	if (snake->body[0][Y_POS] >= 16 || snake->body[0][Y_POS] < 0)
		return (1);
	return (0);
}
