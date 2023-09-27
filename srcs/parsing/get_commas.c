#include "minirt.h"

bool	get_commas3(char *s, char **s2, char **s3)
{
	*s2 = ft_strchr(s, ',');
	if (*s2 == NULL)
		return (false);
	**s2 = '\0';
	++(*s2);
	*s3 = ft_strchr(*s2, ',');
	if (*s3 == NULL)
		return (false);
	**s3 = '\0';
	++(*s3);
	return (true);
}

bool	get_commas4(char *s, char **s2, char **s3, char **s4)
{
	*s2 = ft_strchr(s, ',');
	if (*s2 == NULL)
		return (false);
	**s2 = '\0';
	++(*s2);
	*s3 = ft_strchr(*s2, ',');
	if (*s3 == NULL)
		return (false);
	**s3 = '\0';
	++(*s3);
	*s4 = ft_strchr(*s3, ',');
	if (*s4 == NULL)
		return (false);
	**s4 = '\0';
	++(*s4);
	return (true);
}
