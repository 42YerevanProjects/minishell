#include "../../includes/minishell.h"

/**
 * The function mimics the behavior of pwd command in bash. It returns 0
 * on success and 1 otherwise.
 **/

int	ft_pwd(t_cmd *cmd)
{
	if (ft_matrixlen(cmd->args) > 1)
	{
		ft_minishell_errror("minishell: pwd: Too many args to pwd");
		return (1);
	}
	ft_putstr_fd(ft_getenv("PWD"), cmd->out);
	ft_putstr_fd("\n", cmd->out);
	return (0);
}
