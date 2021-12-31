#include "../../includes/minishell.h"

void	increment_shell_level(t_env *env)
{
	char	*shlvl_value;
	int		shlvl;
	t_env	*head;
	
	head = env;
	shlvl_value = getenv("SHLVL");
	if (ft_strcmp(shlvl_value, "") == 0)
		return ;
	shlvl = ft_atoi(shlvl_value) + 1;
	while (head && head->next)
	{
		if (ft_strncmp("SHLVL", head->value, 5) == 0)
		{
 			head->value = ft_strjoin("SHLVL=", ft_itoa(shlvl));
			return ;
		}
		head = head->next;
	}
}
