#include <minishell.h>

int	token_check(t_token *token)
{
	int	has_command;

	while (token)
	{
		has_command = 0;
		while (token && token->type != PIPE)
		{
			if (token->type == COMMAND)
				has_command = 1;
			if (token->type == INFILE || token->type == OUTFILE ||
				token->type == APPEND)
				if (token->next->type != FILENAME)
					return (printf("Syntax error near '%s\'\n", token->str), 0);
			if (token->type == HEREDOC && token->next->type != DELIMITER)
				return (printf("Syntax error near '%s\'\n", token->str), 0);
			token = token->next;
		}
		if (has_command == 0)
			return (printf("Syntax error near '%s\'\n", token->str), 0);
		if (token && token->type == PIPE)
			token = token->next;
	}
	return (1);
}
