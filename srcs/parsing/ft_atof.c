#include "minirt.h"

bool	ft_atof(char *s, float *ans)
{
	int		i;
	float	sign;
	float	decimal;

	i = (s[0] == '-' || s[0] == '+');
	if (s[i] == '\0' || (s[i] == '.' && s[i + 1] == '\0'))
		return (false);
	sign = (s[0] != '-') - (s[0] == '-');
	*ans = 0;
	while (ft_isdigit(s[i]))
		*ans = 10 * *ans + s[i++] - '0';
	if (s[i] == '.')
	{
		++i;
		decimal = 0.1;
		while (ft_isdigit(s[i]))
		{
			*ans += decimal * (s[i++] - '0');
			decimal *= 0.1;
		}
	}
	*ans *= sign;
	return (s[i] == '\0' && isfinite(*ans));
}

bool	ft_atof_range(char *s, float *ans, float min, float max)
{
	return (ft_atof(s, ans) && *ans >= min && *ans <= max);
}
