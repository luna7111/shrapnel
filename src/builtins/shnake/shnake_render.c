/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   shnake_render.c                                .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/06/23 21:37:50 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/06/23 21:37:51 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include "shnake.h"

void	fill_map_dots(char map[16][16])
{
	int		x_iter;
	int		y_iter;

	x_iter = 0;
	y_iter = 0;
	while (y_iter < 16)
	{
		while (x_iter < 16)
		{
			map[y_iter][x_iter] = '.';
			x_iter ++;
		}
		x_iter = 0;
		y_iter ++;
	}
}

void	draw_stuff_in_map(char map[16][16], t_snake *snake)
{
	int		i;
	char	c;

	map[snake->apple[Y_POS]][snake->apple[X_POS]] = '#';
	i = 0;
	while (i < snake->snake_len && i < 64)
	{
		if (snake->body[i][Y_POS] >= 0 && snake->body[i][Y_POS]
	< 16 && snake->body[i][X_POS] >= 0 && snake->body[i][X_POS] < 16)
		{
			if (i == 0)
				c = 'O';
			else if (i % 2)
				c = 'x';
			else
				c = 'X';
			map[snake->body[i][Y_POS]][snake->body[i][X_POS]] = c;
		}
		i ++;
	}
}

void	render_map(char map[16][16])
{
	int		x_iter;
	int		y_iter;
	char	c;

	x_iter = 0;
	y_iter = 0;
	while (y_iter < 16)
	{
		while (x_iter < 16)
		{
			c = map[y_iter][x_iter];
			if (c == 'O')
				printf(GREEN);
			else if (c == 'x' || c == 'X')
				printf(YELLOW);
			else if (c == '#')
				printf(MAGENTA);
			printf("%c%s", c, RESET);
			x_iter ++;
		}
		x_iter = 0;
		y_iter ++;
		printf("\n");
	}
}

void	print_map(t_snake *snake)
{
	char	map[16][16];

	fill_map_dots(map);
	draw_stuff_in_map(map, snake);
	render_map(map);
	printf(CURSOR_UP_16);
}
