/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalaban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:46:34 by abalaban          #+#    #+#             */
/*   Updated: 2022/01/07 12:46:12 by abalaban         ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	unset_error(char *var)
{
	ft_putstr_fd("minishell: unset: `", STDERR);
	ft_putstr_fd(var, STDERR);
	ft_putstr_fd("': not a valid identifier\n", STDERR);
}

static int	ft_unset_variable(t_cmd *cmd)
{
	int	i;
	int	status;

	i = 1;
	while (cmd->args[i])
	{
		if (!ft_is_valid_identifier(cmd->args[i]))
		{
			unset_error(cmd->args[i++]);
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

int	ft_unset(t_cmd *cmd)
{
	if (ft_matrixlen(cmd->args) == 1)
	{
		ft_minishell_error("minishell: Invalid number of args to unset");
		return (1);
	}
	return (ft_unset_variable(cmd));
}
