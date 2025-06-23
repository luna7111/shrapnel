#include <minishell.h>
#include "expand.h"

static ptrdiff_t	varname_len(char *str)
{
	ptrdiff_t	len;
	char		*end;

	if (ft_strncmp("$\"", str, 2) == 0 || ft_strncmp("$'", str, 2) == 0)
		len = 1;
	else if (ft_strncmp("$?", str, 2) == 0)
		len = 2;
	else if (ft_strncmp("${", str, 2) == 0)
	{
		end = ft_strchr(str, '}');
		if (end == NULL)
			return (0);
		end ++;
		len = end - str;
	}
	else if (*str == '$' && is_alpha_underscore(str[1]))
	{
		end = str + 2;
		while (is_alnum_underscore(*end))
			end++;
		len = end - str;
	}
	else
		return (0);
	return (len);
}

static t_chunk	expand_variable(t_data *data, char *str, ptrdiff_t len)
{
	t_chunk			chunk;
	char			*varname;
	t_enviroment	*env_match;

	chunk.input_size = len;
	if (!ft_strncmp("${", str, 2))
		varname = ft_substr(str, 2, len - 3);
	else
		varname = ft_substr(str, 1, len - 1);
	gctrl_track_ptr(data->gctrl, varname, LOOP_BLOCK);
	if (!ft_strcmp("?", varname))
	{
		chunk.str = ft_itoa(g_exit_status);
		gctrl_track_ptr(data->gctrl, chunk.str, LOOP_BLOCK);
		return (chunk);
	}
	env_match = env_find_node(data->env, varname);
	if (env_match != NULL)
		chunk.str = ft_strdup(env_match->content);
	else
		chunk.str = ft_strdup("");
	gctrl_track_ptr(data->gctrl, chunk.str, LOOP_BLOCK);
	return (chunk);
}

#define NO_QUOTES 0
#define SIMPLE_QUOTES 1
#define DOUBLE_QUOTES 2

static t_chunk	expand_text(t_data *data, char *str)
{
	static int	quote_state = NO_QUOTES;
	int			i;
	t_chunk		chunk;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && quote_state == NO_QUOTES)
			quote_state = SIMPLE_QUOTES;
		else if (str[i] == '\'' && quote_state == SIMPLE_QUOTES)
			quote_state = NO_QUOTES;
		else if (str[i] == '"' && quote_state == NO_QUOTES)
			quote_state = DOUBLE_QUOTES;
		else if (str[i] == '"' && quote_state == DOUBLE_QUOTES)
			quote_state = NO_QUOTES;
		if (varname_len(&str[i]) > 0 && quote_state != SIMPLE_QUOTES)
			break ;
		i++;
	}
	if (str[i] == '\0')
		quote_state = NO_QUOTES;
	chunk.input_size = i;
	chunk.str = ft_substr(str, 0, i);
	gctrl_track_ptr(data->gctrl, chunk.str, LOOP_BLOCK);
	return (chunk);
}

static t_chunk	expand_next_chunk(t_data *data, char *str)
{
	t_chunk		chunk;
	ptrdiff_t	varname;

	varname = varname_len(str);
	if (varname > 0)
		chunk = expand_variable(data, str, varname);
	else
		chunk = expand_text(data, str);
	return (chunk);
}

char	*expand_input(t_data *data, char *str)
{
	t_chunk	current_chunk;
	char	*output;

	output = ft_strdup("");
	gctrl_track_ptr(data->gctrl, output, LOOP_BLOCK);
	while (*str != '\0')
	{
		current_chunk = expand_next_chunk(data, str);
		output = ft_strjoin(output, current_chunk.str);
		gctrl_track_ptr(data->gctrl, output, LOOP_BLOCK);
		str += current_chunk.input_size;
	}
	(void)expand_text(data, str);
	return (output);
}
