#include "../../includes/minishell.h"

/**
 * The function updates the OLDPWD and PWD environment variables
 * after changing the directory. Returns 0 on success, 1 otherwise.
 **/

static int	update_env_wds(char *oldpwd, int status)
{
	char	*pwd;
	t_cmd	export;
	/* If status is 1 (smth wrong happened) */
	if (status)
	{
		free(oldpwd);
		return (ft_minishell_error("minishell: cd: No such file or directory"));
	}
	/* Get the current PWD and export it by updating the old one */
	pwd = getcwd(NULL, 0);
	export.args = ft_calloc(3, sizeof(char *));
	export.args[0] = ft_strdup("");
	export.args[1] = ft_strjoin("PWD=", pwd);
	ft_export(&export);
	/* Free the memory used */
	ft_free_matrix(export.args);
	free(pwd);
	/* Construct export for the OLDPWD and export it by updating the old one */
	export.args = ft_calloc(3, sizeof(char *));
	export.args[0] = ft_strdup("");
	export.args[1] = ft_strjoin("OLDPWD=", oldpwd);
	ft_export(&export);
	/* Free the memory used */
	ft_free_matrix(export.args);
	free(oldpwd);
	return (status);
}

/**
 * THe function changes the directory from minishell. Returns 0
 * on success, 1 otherwise.
 **/

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

/**
 * The function mimics the behavior of the command cd in bash. It 
 * changes the directory and updates the OLDPWD and PWD
 * fields of the environment properly. Returns 0, on success, 1
 * otherwise.
 **/

int	ft_cd(t_cmd *cmd)
{
	int		status;
	char	*oldpwd;

	status = 1;
	/* No matter where you are, absolute paths should work */
	if (!cmd->args[1] || cmd->args[1][0] == '/' || cmd->args[1][0] == '-')
		oldpwd = ft_strdup(ft_getenv("PWD"));
	/* else if it is not an absolute path */
	else
		oldpwd = getcwd(NULL, 0);
	/* If getcwd returned NULL for some reason */
	if (!oldpwd)
	{
		perror("cd: could not retrive current directory");
		return (0);
	}
	/* If the command is just "cd" => go to $HOME */
	if (ft_matrixlen(cmd->args) == 1)
	{
		if (ft_getenv("HOME"))
			status = ft_abs(chdir(ft_getenv("HOME")));
		else
		{
			free(oldpwd);
			return (ft_minishell_error("cd: HOME is not set"));
		}
	}
	/* Perform the change of the directory */
	else
	{
		if (ft_change_dir(cmd, &status, oldpwd))
			return (1);
	}
	/* Update PWD and OLDPWD environment variables */
	return (update_env_wds(oldpwd, status));
}

