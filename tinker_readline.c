/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   tinker_readline.c                              .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/04/16 10:36:48 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/04/16 10:46:10 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char **argv, char **env)
{
	while (1)
		printf("%s\n", readline("Minishell> "));
}
