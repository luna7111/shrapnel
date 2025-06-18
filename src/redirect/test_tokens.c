/* ************************************************************************** */
/*                                                                            */
/*                                                    _.._  .           .     */
/*   test_tokens.c                                  .' .-'`        *          */
/*                                                 /  /       +        *      */
/*   By: ldel-val <ldel-val@student.42madrid.com>  |  |           *           */
/*                                                 \  '.___.;       +         */
/*   Created: 2025/06/10 01:28:35 by ldel-val       '._  _.'   .        .     */
/*   Updated: 2025/06/18 16:25:59 by ldel-val          ``                     */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token *create_token(t_gctrl *gctrl, const char *str, int type, size_t output_len)
{
    t_token *new_token = gctrl_malloc(gctrl, LOOP_BLOCK, sizeof(t_token));
    if (!new_token)
        return NULL;

    new_token->str = strdup(str);
	gctrl_track_ptr(gctrl, new_token->str, LOOP_BLOCK);
    new_token->output_len = output_len;
    new_token->type = type;
    new_token->quoted = 0;
    new_token->next = NULL;

    return new_token;
}

t_token *last_token(t_token *token)
{
	if (!token)
		return NULL;
	while (token->next)
		token = token->next;
	return token;
}

void	token_add_back(t_token **list, t_token *token)
{
	if (!*list)
	{
		token->next = *list;
		*list = token;
		return ;
	}
	if (token)
		last_token(*list)->next = token;
	return ;	
}

t_token *gen_test2(t_data *data)
{
		t_token *list = NULL;
		token_add_back(&list, create_token(data->gctrl, "cat", COMMAND, 3));
		token_add_back(&list, create_token(data->gctrl, "-e", COMMAND, 2));
		token_add_back(&list, create_token(data->gctrl, "-a", COMMAND, 2));
		token_add_back(&list, create_token(data->gctrl, "Makefile", COMMAND, 2));
		token_add_back(&list, create_token(data->gctrl, "|", PIPE, 1));
		token_add_back(&list, create_token(data->gctrl, "wc", COMMAND, 2));
		token_add_back(&list, create_token(data->gctrl, "-l", COMMAND, 2));
		return (list);
}

t_token *gen_test1(t_data *data)
{
		t_token *list = NULL;
		token_add_back(&list, create_token(data->gctrl, "cat", COMMAND, 3));
		token_add_back(&list, create_token(data->gctrl, "<", INFILE, 1));
		token_add_back(&list, create_token(data->gctrl, "log.temp", FILENAME, 8));
		token_add_back(&list, create_token(data->gctrl, "<", INFILE, 1));
		token_add_back(&list, create_token(data->gctrl, "Makefile", FILENAME, 8));
		token_add_back(&list, create_token(data->gctrl, "-e", COMMAND, 2));
		token_add_back(&list, create_token(data->gctrl, "-a", COMMAND, 2));
		token_add_back(&list, create_token(data->gctrl, "|", PIPE, 1));
		token_add_back(&list, create_token(data->gctrl, "wc", COMMAND, 2));
		token_add_back(&list, create_token(data->gctrl, "-l", COMMAND, 2));
		token_add_back(&list, create_token(data->gctrl, "<", INFILE, 1));
		token_add_back(&list, create_token(data->gctrl, "testfile1", FILENAME, 8));

		return (list);
}
