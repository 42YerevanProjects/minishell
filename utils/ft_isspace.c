#include "../includes/minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\f'
		|| c == '\n' || c == '\r');
}
