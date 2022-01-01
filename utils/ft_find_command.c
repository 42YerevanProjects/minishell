#include "../includes/minishell.h"

t_cmd	*ft_find_command(pid_t pid)
{
	int	i;

	i = 0;
	while (i < g_mini.cmd_count)
	{
		if (g_mini.fam[i] == pid)
			return (&g_mini.commands[i]);
		i++;
	}
	return (NULL);
}
