#include "../../includes/minishell.h"

int	ft_is_valid_declaration(char *decl)
{
	int		ret;
	char	*name;

	name = ft_separate_identifier(decl);
	ret = ft_is_valid_identifier(name);
	free(name);
	return (ret);
}
