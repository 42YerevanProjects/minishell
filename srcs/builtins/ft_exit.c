#include "../../includes/minishell.h"

/**
 * The function terminates the caller.
 **/

static void	terminate(int exit_code)
{
	/* If exit is done in the main process */
	if(g_mini.cmd_count == 1)
	{
		/* If no error occured */
		if (!g_mini.status)
			exit(exit_code);
	}
	/* If exit in a child process */
	else
	{
		/* if no  exit code specified, exit with the status */
		if (!exit_code)
			exit(g_mini.status);
		/* Else if tere is one, exit with code */
		exit(exit_code);
	}
}

/**
 * The function mimics the behavior of the command exit in bash.
 **/

void	ft_exit(t_cmd *cmd)
{
	int	exit_code;

	/* When no errors occured */
	g_mini.status = 0;
	exit_code = 0;
	/* If there is only one process: the main */
	if (g_mini.cmd_count == 1)
		ft_putstr_fd("exit 💚\n", STDERR);
	/* If the command has no exit code specified, then exit with 0 */
	if (ft_matrixlen(cmd->args) == 1)
		exit(0);
	/* If the command contains non numeric characters */
	if (!ft_isnum(cmd->args[1]))
	{
		exit_code = 255;
		ft_minishell_error("minisell: exit: numeric argument required");
	}
	/* Else if the command does not contain non-numeric characters */
	else
	{
		/* If ther is just one status code */
		if (ft_matrixlen(cmd->args) == 2)
			exit_code = ft_atoi(cmd->args[1]);
		/* Else there are more than one numbers */
		else
			g_data.status = ft_minishell_error("minishell: exit: too many arguments");
	}
	/* Terminating the process who called exit */
	terminate(exit_code);
}

