#include "../includes/minishell.h"

int	ft_heredoc_size(char ** token_array)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (token_array[i])
	{
		if (!ft_strcmp(token_array[i], "<<"))
			len++;
		i++;
	}
	return (len);
}
