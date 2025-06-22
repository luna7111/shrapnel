#include <minishell.h>

int	token_check(t_token *token)
{
	int	has_command;
	t_token	*buf;

	while (token)
	{
		has_command = 0;
		while (token && token->type != PIPE)
		{
			if (token->type == COMMAND)
				has_command = 1;
			if (token->type == INFILE || token->type == OUTFILE ||
				token->type == APPEND)
				if (token->next == NULL || token->next->type != FILENAME)
					return (printf("Syntax error near '%s\'\n", token->str), 0);
			if (token->type == HEREDOC && (token->next == NULL || token->next->type != DELIMITER))
				return (printf("Syntax error near '%s\'\n", token->str), 0);
			buf = token;
			token = token->next;
		}
		if (has_command == 0)
		{
			if	(token == NULL)
				return (printf("Syntax error near '%s\'\n", buf->str), 0);
			else
				return (printf("Syntax error near '%s\'\n", token->str), 0);
		}
		if (token && token->type == PIPE)
		{
			if (token->next == NULL)
				return (printf("Syntax error near '%s\'\n", token->str), 0);
			else
				token = token->next;
		}
	}
	return (1);
}
