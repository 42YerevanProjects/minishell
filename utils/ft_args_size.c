#include "../includes/minishell.h"

int	ft_args_size(int index)
{
	int		size;

	size = 0;
	while (g_mini.tokens->token_array[index] && 
			ft_strcmp(g_mini.tokens->token_array[index], "|"))
	{
		size++;
		index++;
	}
	return size + 1;
}
