#include "../../includes/minishell.h"

char	*ft_separate_identifier(char *var)
{
	int		i;
	char	*name;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	name = ft_calloc(i + 1, sizeof(char));
	i = 0;
	while (var[i] && var[i] != '=')
	{
		name[i] = var[i];
		i++;
	}
	return (name);
}
