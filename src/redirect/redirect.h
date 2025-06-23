/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   redirect.h                                     .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/06/23 21:38:23 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/06/23 21:38:23 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

size_t	count_cmd_params(t_token *tokens);
char	**command_tokens_to_array(t_data *data, t_token *tokens);
int		open_fd_in(t_data *data, t_token *tokens, int fd);
int		open_fd_out(t_data *data, t_token *token, int fd);

#endif
