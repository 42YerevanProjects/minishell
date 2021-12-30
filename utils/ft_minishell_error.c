#include "../includes/minishell.h"

int	ft_minishell_error(char *msg)
{
	ft_putstr_fd(msg, STDERR);
	ft_putstr_fd("\n", STDERR);
	return (1);
}
