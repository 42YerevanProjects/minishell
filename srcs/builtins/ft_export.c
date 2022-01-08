/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shovsepy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:34:45 by shovsepy          #+#    #+#             */
/*   Updated: 2022/01/07 12:36:09 by shovsepy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	export_error(char *var, int *status)
{
	ft_putstr_fd("minishell: export: `", STDERR);
	ft_putstr_fd(var, STDERR);
	ft_putstr_fd("': not a valid identifier\n", STDERR);
	*status = 1;
}

static void	ft_export_variable(t_cmd *cmd, int *status)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		if (!ft_is_valid_declaration(cmd->args[i]))
		{
			export_error(cmd->args[i++], status);
			continue ;
		}
		if (ft_env_contains(cmd->args[i]))
		{
			if (ft_strchr(cmd->args[i], '='))
				ft_remove_from_env(cmd->args[i]);
			else
			{
				*status = 0;
				i++;
				continue ;
			}
		}
		ft_add_to_env(ft_strdup(cmd->args[i]));
		*status = 0;
		i++;
	}
}

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
