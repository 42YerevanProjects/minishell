#include "../../includes/minishell.h"

/**
 * The function mimics the behavior of the env in bash. Returns 0
 * on success, 1 otherwise.
 **/

int	ft_env(t_cmd *cmd)
{
	t_env	*head;

	head = g_mini.env;
	if (ft_matrixlen(cmd->args) > 1)
	{
		ft_minishell_error("minishell: env: Too many args to env");
		return (1);
	}
	while (head)
	{
		ft_putstr_fd(head->value, cmd->out);
		ft_putstr_fd("\n", cmd->out);
		head = head->next;
	}
	return (0);
}
