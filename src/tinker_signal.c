/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   tinker_signal.c                                .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/04/17 18:45:17 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/04/17 19:40:58 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <garbage_control.h>
#include <signal.h>
#include <unistd.h>

void	handler(int num)
{
	printf("Signal! %d PID: %d\n", num, getpid());
}

int main()
{
	signal(SIGINT, handler);
	while (1);
}
