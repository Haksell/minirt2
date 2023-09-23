#include "minirt.h"

static bool	get_commas(char *s, char **s2, char **s3)
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

static bool	parse_component(char *s, float *x)
{
	int	n;
	int	i;

	if (s[0] == '\0')
		return (false);
	n = 0;
	i = 0;
	while (ft_isdigit(s[i]))
	{
		n = 10 * n + s[i] - '0';
		if (n > 255)
			return (false);
		++i;
	}
	*x = n;
	return (s[i] == '\0');
}

bool	parse_color(char *s, t_vec3 *color)
{
	char	*s2;
	char	*s3;

	return (get_commas(s, &s2, &s3)
		&& parse_component(s, (float *)color + X)
		&& parse_component(s2, (float *)color + Y)
		&& parse_component(s3, (float *)color + Z));
}

bool	parse_coord(char *s, t_vec3 *coord)
{
	char	*s2;
	char	*s3;

	return (get_commas(s, &s2, &s3)
		&& ft_atof(s, (float *)coord + X)
		&& ft_atof(s2, (float *)coord + Y)
		&& ft_atof(s3, (float *)coord + Z));
}

bool	parse_normalized_vector(char *s, t_vec3 *vector)
{
	printf("parse_normalized_vector: %s\n", s);
	return (parse_coord(s, vector)
		&& is_close(vec3_length_squared(*vector), 1));
}