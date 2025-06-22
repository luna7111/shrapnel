#include <minishell.h>

size_t	env_len(t_enviroment *env)
{
	size_t	size;

	size = 0;
	while (env)
	{
		env = env->next;
		size ++;
	}
	return (size);
}
