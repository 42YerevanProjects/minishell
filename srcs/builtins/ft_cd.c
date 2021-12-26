#include "../../includes/minishell.h"

static int	update_env_wds(t_mini *mini, char *oldpwd, int status)
{
	//TODO: Update PWD and OLDPWD after doing export
}

static int	ft_change_dir(t_cmd *cmd, int *status, char *oldpwd)
{
	/* if it is "cd -" go to oldpwd */
	if (cmd->args[1][0] == '-' && cmd->args[1][1] == '\0')
	{
		if (ft_getenv("OLDPWD"))
		{
			*status = ft_abs(chdir(ft_getenv("OLDPWD")));
			if (!*status)
			{
				ft_putstr_fd(ft_getenv("OLDPWD"), cmd->out);
				ft_putstr_fd("\n", cmd->out);
			}
		}
		else
		{
			free(oldpwd);
			return (ft_minishell_error("cd: OLDPWD not set"));
		}
	}
	/* else if a path is specified */
	else
		*status = ft_abs(chdir(cmd->args[1]));
	return (0);
}

int	ft_cd(t_mini *mini, t_cmd *cmd)
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
		if (ft_change_path(cmd, &status, oldpwd))
			return (1);
	}
	/* update PWD and OLDPWD environment variables */
	return (update_env_wds(mini, oldpwd, status));
}

