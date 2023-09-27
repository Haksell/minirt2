#include "minirt.h"

int	arrlen(char **lines)
{
	int	n;

	n = 0;
	while (lines[n] != NULL)
		++n;
	return (n);
}
