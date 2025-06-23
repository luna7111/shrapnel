#include <minishell.h>

int	is_valid_number(char *str)
{
	char	*buf;

	buf = ft_itoa(ft_atoi(str));
	if (ft_strcmp(str, buf))
	{
		free(buf);
		return (0);
	}
	free(buf);
	return (1);
}

void	set_shlvl(t_data *data)
{
	t_enviroment	*shlvl;
	char			*shlvl_val;

	shlvl = env_find_node(data->env, "SHLVL");
	if (shlvl == NULL)
		env_add_node(data, "SHLVL=1");
	else if (is_valid_number(shlvl->content))
	{
		shlvl_val = ft_itoa(ft_atoi(shlvl->content) + 1);
		env_set_node(data, "SHLVL", shlvl_val);
		free(shlvl_val);
	}
	else
		env_set_node(data, "SHLVL", "1");
}

void	set_pwd(t_data *data)
{
	char			pwd[PATH_MAX];
	char			*rawvar;
	t_enviroment	*node;

	node = env_find_node(data->env, "PWD");
	getcwd(pwd, sizeof(pwd));
	if (node == NULL)
	{
		rawvar = ft_strjoin("PWD=", pwd);
		env_add_node(data, rawvar);
		free(rawvar);
	}
	else
	{
		env_set_node(data, "PWD", pwd);
	}
}
