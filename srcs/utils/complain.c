#include "minirt.h"

static void	complain(char *error_message)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd(error_message, STDERR_FILENO);
}

bool	complain_bool(char *error_message)
{
	complain(error_message);
	return (false);
}

int	complain_int(char *error_message)
{
	complain(error_message);
	return (-1);
}

void	*complain_ptr(char *error_message)
{
	complain(error_message);
	return (NULL);
}
