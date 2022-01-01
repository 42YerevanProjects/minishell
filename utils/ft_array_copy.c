#include "../includes/minishell.h"

char	**ft_array_copy(char **args)
{
	char	**copy;
	int		i;

	i = ft_matrixlen(args) + 1;
	copy = (char **)malloc(sizeof(char *) * i);
	i = 0;
	while (args[i])
	{
		copy[i] = ft_strdup(args[i]);
		i++;
	}
	copy[i] = NULL;
	return copy;
}
