#include "../../includes/minishell.h"

/**
 * The function outputs the error message in case of non valid
 * argument to the export command.
 **/
static void	export_error(char *var, int *status)
{
	ft_putstr_fd("minishell: export: `", STDERR);
	ft_putstr_fd(var, STDERR);
	ft_putstr_fd("': not a valid identifier\n", STDERR);
	*status = 1;
}

/**
 * The function exprts the variable to the environment. It also
 * handles the errors encountered.
 **/

static void	ft_export_variable(t_cmd *cmd, int *status)
{
	int	i;

	i = 1;
	/* Iterate over the arguments to be exported */
	while (cmd->args[i])
	{
		/* If not a valid env variable name, then output error and continue */
		if (!ft_is_valid_declaration(cmd->args[i]))
		{
			export_error(cmd->args[i++], status);
			continue ;
		}
		/* If the env alredy contains the argument specified */
		if (ft_env_contains(cmd->args[i]))
		{
			/* If there is a new valu, remove the old one from env and override later */
			if (ft_strchr(cmd->args[i], '='))
				ft_remove_from_env(cmd->args[i]);
			/* No value specified */
			else
			{
				*status = 0;
				i++;
				continue ;
			}
		}
		/* Add the argumen to the environment */
		ft_add_to_env(ft_strdup(cmd->args[i]));
		*status = 0;
		i++;
	}
}

/**
 * The function mimics the behavior of the export builtin.
 * Returns 0 on success, 1 otherwise.
 **/

int	ft_export(t_cmd *cmd)
{
	int	status;

	status = 0;
	if (ft_matrixlen(cmd->args) == 1)
		ft_print_env(cmd->out);
	else
		ft_export_variable(cmd, &status);
	return (status);
}
