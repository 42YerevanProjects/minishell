#include "../../includes/minishell.h"

/**
 * The function outputs the error in case variable is not a valid identifier.
 **/

static void	unset_error(char *var)
{
	ft_putstr_fd("minishell: unset: `", STDERR);
	ft_putstr_fd(var, STDERR);
	ft_putstr_fd("': not a valid identifier\n", STDERR);
}

/**
 * Unsets the variable from the environment if the variable is present. Outputs errro
 * if the variable is not a valid identifier. Returns 0 on success, 1 otherwise.
 **/

static int	ft_unset_variable(t_cmd *cmd)
{
	int	i;
	int	status;

	i = 1;
	while (cmd->args[i])
	{
		if (!ft_isvalididentifier(cmd->args[i]))
		{
			unset_error(cmd->arg[i++]);
			status = 1;
			continue ;
		}
		if (ft_env_contains(cmd->args[i]))
		{
			ft_remove_from_env(cmd->args[i]);
			status = 0;
		}
		i++;
	}
	return (status);
}

/**
 * The function mimics the behavior of the unset command in bash. It
 * returns 0 on success, 1 otherwise.
 **/

int	ft_unset(t_cmd *cmd)
{
	if (ft_matrixlen(cmd->args) == 1)
	{
		ft_minishell_error("minishell: unset: Invalid number of args to unset");
		return (1);
	}
	return ft_unset_variable(cmd);
}
