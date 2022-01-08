/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shovsepy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:34:45 by shovsepy          #+#    #+#             */
/*   Updated: 2022/01/07 12:36:09 by shovsepy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_oldpwd(t_cmd *cmd)
{
	if (!cmd->args[1] || cmd->args[1][0] == '/' || cmd->args[1][0] == '-')
		return (ft_strdup(ft_getenv("PWD")));
	else
		return (getcwd(NULL, 0));
}

static int	update_env_wds(char *oldpwd, int status)
{
	char	*pwd;
	t_cmd	export;

	if (status)
	{
		free(oldpwd);
		return (ft_minishell_error("minishell: cd: No such file or directory"));
	}
	pwd = getcwd(NULL, 0);
	export.args = ft_calloc(3, sizeof(char *));
	export.args[0] = ft_strdup("");
	export.args[1] = ft_strjoin("PWD=", pwd);
	ft_export(&export);
	ft_free_matrix(export.args);
	free(pwd);
	export.args = ft_calloc(3, sizeof(char *));
	export.args[0] = ft_strdup("");
	export.args[1] = ft_strjoin("OLDPWD=", oldpwd);
	ft_export(&export);
	ft_free_matrix(export.args);
	free(oldpwd);
	return (status);
}

static int	ft_change_dir(t_cmd *cmd, int *status, char *oldpwd)
{
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
	else
		*status = ft_abs(chdir(cmd->args[1]));
	return (0);
}

int	ft_cd(t_cmd *cmd)
{
	int		status;
	char	*oldpwd;

	status = 1;
	oldpwd = get_oldpwd(cmd);
	if (!oldpwd)
	{
		perror("cd: could not retrive current directory");
		return (0);
	}
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
	else
		if (ft_change_dir(cmd, &status, oldpwd))
			return (1);
	return (update_env_wds(oldpwd, status));
}
