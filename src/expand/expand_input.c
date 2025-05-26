#include <minishell.h>

typedef struct s_chunk
{
	char	*str;
	size_t	input_size;
	size_t	output_size;
}	t_chunk;

void	resize_array(t_data *data, t_chunk **array, size_t len, size_t new_len)
{
	t_chunk	*new;
	size_t	i;

	new = gctrl_malloc(data->gctrl, LOOP_BLOCK, new_len * sizeof(t_chunk));
	i = 0;
	while (i < len)
	{
		new[i] = *array[i];
		i++;
	}
	*array = new;
}

int	is_alpha_underscore(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int is_alnum_underscore(char c)
{
	return (ft_isalnum(c) || c == '_');
}

ptrdiff_t	varname_len(char *str)
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

t_chunk	expand_variable(t_data *data, char *str, ptrdiff_t len)
{
	t_chunk	chunk;
	char	*varname;
	t_enviroment	*env_match;

	chunk.input_size = len;
	if (!ft_strncmp("${", str, 2))
		varname = ft_substr(str, 2, len - 3);
	else
		varname = ft_substr(str, 1, len - 1);
	gctrl_track_ptr(data->gctrl, varname, LOOP_BLOCK);
	if (!ft_strcmp("?", varname))
	{
		chunk.str = ft_itoa(data->last_exit_code);
		gctrl_track_ptr(data->gctrl, chunk.str, LOOP_BLOCK);
		chunk.output_size = ft_strlen(chunk.str);
		return (chunk);
	}
	env_match = env_find_node(data->env, varname);
	if (env_match != NULL)
		chunk.str = ft_strdup(env_match->content);	
	else
		chunk.str = ft_strdup("");
	gctrl_track_ptr(data->gctrl, chunk.str, LOOP_BLOCK);
	chunk.output_size = ft_strlen(chunk.str);
	return (chunk);
}

#define NO_QUOTES 0
#define SIMPLE_QUOTES 1
#define DOUBLE_QUOTES 2

t_chunk expand_text(t_data *data, char *str)
{
	t_chunk	chunk;
	static int	quote_state = NO_QUOTES;
	int		i;

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
	chunk.output_size = i;
	chunk.str = ft_substr(str, 0, i);
	gctrl_track_ptr(data->gctrl, chunk.str, LOOP_BLOCK);
	return (chunk);
}

/*
char	*expand_input(t_data *data, char *str)
{
	t_chunk	*expanded_array;
	size_t	array_size;
	size_t	i;
	ptrdiff_t	expand_len;
	
	array_size = 8;
	expanded_array = gctrl_malloc(data->gctrl, LOOP_BLOCK, array_size);
	i = 0;
	while (*str)
	{
		expand_len = varname_len(str);
		if (expand_len > 0)
		{
			expanded_array[i] = expand_variable(data, str, expand_len);
			printf("%s", expanded_array[i].str);
		}
		else
		{
			expanded_array[i] = expand_text(data, str);
			printf("i = %ld\n", i);
			printf("ear i s %ld\n", expanded_array[i].input_size);
			printf("ear o s %ld\n", expanded_array[i].output_size);
			printf("ear str %s\n", expanded_array[i].str);
		}
		str += expanded_array[i].input_size;
		i++;
		break ;
	}
	return (str);
}*/

t_chunk	expand_next_chunk(t_data *data, char *str)
{
	t_chunk		chunk;
	ptrdiff_t	varname;

	varname = varname_len(str);
	if (varname > 0)
		chunk = expand_variable(data, str, varname);
	else
		chunk = expand_text(data, str);
	return(chunk);
}

char	*expand_input(t_data *data, char *str)
{
	t_chunk current_chunk;
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
	return (output);
}
