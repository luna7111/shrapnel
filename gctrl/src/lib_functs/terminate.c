/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   terminate.c                                    .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/03/16 10:15:39 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/04/17 02:58:52 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <garbage_control.h>

#ifndef VERBOSE

void	gctrl_terminate(t_gctrl *gctrl)
{
	gctrl_cleanup(gctrl, ALL_BLOCKS);
	free(gctrl->dump);
	free(gctrl);
}
#else

void	gctrl_terminate(t_gctrl *gctrl)
{
	gctrl_print_dump(*(gctrl->dump), "Memory that wasn't manually freed:\n");
	gctrl_cleanup(gctrl, ALL_BLOCKS);
	free(gctrl->dump);
	free(gctrl);
}
#endif
