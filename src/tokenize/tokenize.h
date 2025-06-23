/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   tokenize.h                                     .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/06/23 21:38:45 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/06/23 21:38:46 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

// Funciones auxiliares para nodos y tokens
void	create_and_add_token(t_data *data, t_token **list, char *str,
			size_t len);
t_token	*new_node(t_gctrl *gctrl);
void	token_add_back(t_token **lst, t_token *new);
t_token	*last_node(t_token *lst);
void	unquote_node(t_data *data, t_token *token);
#endif
