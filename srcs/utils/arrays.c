#include "minirt.h"

int	arrlen(char **lines)
{
	int	n;

	n = 0;
	while (lines[n] != NULL)
		++n;
	return (n);
}

bool	includes(char **arr, char *s)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		if (ft_strcmp(arr[i], s) == 0)
			return (true);
		++i;
	}
	return (false);
}
