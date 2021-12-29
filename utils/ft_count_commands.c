#include "../includes/minishell.h"

int	ft_count_commands(char **token_array)
{
	int	i;
	int	c;

	if (!token_array)
		return (0);
	i = 0;
	c = 1;
	while (token_array[i])
	{
		if (token_array[i][0] == '|' && token_array[i][1] == '\0')
			c++;
		i++;
	}
	return (c);
}
