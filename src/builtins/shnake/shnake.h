/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   shnake.h                                       .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/06/23 15:19:53 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/06/23 15:27:02 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHNAKE_H
# define SHNAKE_H

typedef struct s_snake
{
	int	apple[2];
	int	snake_len;
	int	snake_direction;
	int	body[64][2];
}	t_snake;

# define X_POS 0
# define Y_POS 1
# define DIRECTION 2

# define D_RIGHT 0
# define D_UP 1
# define D_LEFT 2
# define D_DOWN 3
# define GREEN "\001\x1B[32m\002"
# define YELLOW "\001\x1B[33m\002"
# define MAGENTA "\001\x1B[35m\002"
# define RESET "\001\x1B[0m\002"
# define CURSOR_UP_16 "\033[16A"

int		get_head_direction(int current);
void	busy_wait(unsigned long int units);
int		pseudo_random_number(t_snake *snake);
void	eat_apple(t_snake *snake);
int		check_death(t_snake *snake);

void	shnake_sigint_handler(int sig);
void	shnake_sigquit_handler(int sig);
void	set_terminal_mode(int mode);

void	print_map(t_snake *snake);

#endif
