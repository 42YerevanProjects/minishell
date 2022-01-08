#include "../../includes/minishell.h"

/**
 * The function mimics the behavior of pwd command in bash. It returns 0
 * on success and 1 otherwise.
 **/

int	ft_pwd(t_cmd *cmd)
{
	char	*pwd;

	pwd = ft_getenv("PWD");
	if (pwd)
		ft_putstr_fd(pwd, cmd->out);
	else
		ft_minishell_error("minishell: PWD is not set");
	ft_putstr_fd("\n", cmd->out);
	return (0);
}
