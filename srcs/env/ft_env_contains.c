#include "../../includes/minishell.h"

int	ft_env_contains(char *var)
{
	char	*ret;
	char	*name;

	name = ft_separate_identifier(var);
	ret = ft_getenv(name);
	free(name);
	if (ret)
		return (1);
	return (0);
}
