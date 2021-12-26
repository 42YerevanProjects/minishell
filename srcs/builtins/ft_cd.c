#include "../../includes/minishell.h"

int	ft_cd(t_cmd *cmd)
{
	int		status;
	char	*oldpwd;

	status = 1;
	oldpwd = getcwd(NULL, 0);
	/* if getcwd returned NULL for some reason */
	if (!oldpwd)
	{
		perror("cd: could not retrive current directory");
		return (0);
	}
	/* if the command is just "cd" => go to $HOME */
	if (ft_matrixlen(cmd->args) == 1)
	{
		if (ft_getenv("HOME"))
			status = ft_abs(chdir(ft_getenv("HOME")));
		else
		{
			free(oldpwd);
			return (ft_minishell_error("cd: HOME is not set");
		}
	}
	/* perform the change of the directory */
	else
	{
		//TODO: deal with cd
	}

}
