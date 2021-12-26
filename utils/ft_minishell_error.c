#include "../includes/minishell.h"

int	ft_error(char *name, char *desc)
{
	ft_putstr_fd(msg, STDERR);
	ft_putstr_fd("\n", STDERR);
	return (1);
}
