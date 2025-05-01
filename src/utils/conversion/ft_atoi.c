#include <minishell.h>

int	ft_atoi(const char *nptr)
{
	int	number;
	int	sign;

	sign = 1;
	number = 0;
	while (*nptr == ' ' || (*nptr <= '\r' && *nptr >= '\t'))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr ++;
	}
	while (ft_isdigit(*nptr))
	{
		number *= 10;
		number += *nptr - '0';
		nptr++;
	}
	return (number * sign);
}
