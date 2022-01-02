#include "../../includes/minishell.h"

/**
 * The function outputs the environment. I wraps the values
 * of the environment variables with double quotes.
 **/

void	ft_print_env(int fd)
{
	t_env	*head;
	int		i;

	head = g_mini.env;
	while (head)
	{
		i = 0;
		ft_putstr_fd("declare -x ", fd);
		while (head->value[i] && head->value[i] != '=')
			ft_putchar_fd(head->value[i++], fd);
		ft_putstr_fd("=\"", fd);
		i++;
		while (head->value[i])
			ft_putchar_fd(head->value[i++], fd);
		ft_putstr_fd("\"\n", fd);
		head = head->next;
	}
}
