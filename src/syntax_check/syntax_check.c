#include <minishell.h>

#define NO_QUOTES 0
#define SIMPLE_QUOTES 1
#define DOUBLE_QUOTES 2

int	quote_check(char *input)
{
	int	quote_state;

	quote_state = NO_QUOTES;
	while (*input != '\0')
	{
		if (*input == '\'' && quote_state == NO_QUOTES)
			quote_state = SIMPLE_QUOTES;
		else if (*input == '\'' && quote_state == SIMPLE_QUOTES)
			quote_state = NO_QUOTES;
		else if (*input == '"' && quote_state == NO_QUOTES)
			quote_state = DOUBLE_QUOTES;
		else if (*input == '"' && quote_state == DOUBLE_QUOTES)
			quote_state = NO_QUOTES;
		input ++;
	}
	return (!quote_state);
}

int	brace_check(char *input)
{
	int	brace_state;

	brace_state = 0;
	while (*input != '\0')
	{
		if (!ft_strncmp("${", input, 2))
			brace_state = 1;
		else if (*input == '}' && brace_state == 1)
			brace_state = 0;
		input ++;
	}
	return (!brace_state);
}

int	syntax_check(char *input)
{
	if (quote_check(input) == 0)
	{
		printf("Syntax error: unclosed quotes.\n");
		return (0);
	}
	if (brace_check(input) == 0)
	{
		printf("Syntax error: unclosed braces\n");
		return (0);
	}
	return (1);
}
