#include "../../includes/minishell.h"

static char	*get_env_name(char *value)
{
	char	*env_name;
	int		size;
	int		i;

	i = 0;
	while (value[i] != '=')
		i++;
	size = i;
	env_name = malloc(size + 1);
	i = 0;
	while (i < size)
	{
		env_name[i] = value[i];
		i++;
	}
	return env_name;
}

void	increment_shell_level(t_env *env)
{
	char	*env_name;
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
		env_name = get_env_name(head->value); 
		if (ft_strcmp("SHLVL", env_name) == 0)
		{
			head->value = ft_strjoin("SHLVL=", ft_itoa(shlvl));
			ft_memdel(env_name);
			return ;
		}
		head = head->next;
	}
}
