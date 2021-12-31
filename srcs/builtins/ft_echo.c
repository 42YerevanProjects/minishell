#include "../../includes/minishell.h"

/**
 * The function checks for the option n. It also checks for valid option n.
 * The option starts with '-' and can be followed by many 'n's. Anything
 * other than the format specified will result in 0. It it is the option n,
 * the 1 will be returned.
 **/

static int	is_with_option_n(char **args)
{
	int	i;

	i = 1;
	if (ft_strlen(args[1]) < 2 || args[1][0] != '-' ||  args[1][1] != 'n')
		return (0);
	while (args[1][i])
	{
		if (args[1][i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

/**
 * The function mimics the behavior of the command echo in bash. It also
 * supports the option -n. Returns 0 on success.
 **/

int	ft_echo(t_cmd *cmd)
{
	int	opt_flag;
	int	i;

	/* Get the option flag */
	opt_flag = is_with_option_n(cmd->args);
	/* Pass to the next argument. Not taking option n if exists */
	if (opt_flag)
		i = 2;
	else
		i = 1;
	/* If echo has no arguments */
	if (!cmd->args[i])
	{
		/* If there is no option n */
		if (!opt_flag)
			ft_putstr_fd("\n", cmd->out);
		return (0);
	}
	/* Iterate over the arguumens of echo */
	while (cmd->args[i])
	{
		/* Output the argument */
		ft_putstr_fd(cmd->args[i], cmd->out);
		i++;
		if(cmd->args[i])
			ft_putstr_fd(" ", cmd->out);
	}
	/* Output a new line if there is no option n */
	if (!opt_flag)
		ft_putstr_fd("\n", cmd->out);
	return (0);
}

