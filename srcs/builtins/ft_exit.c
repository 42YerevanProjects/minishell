/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shovsepy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:34:45 by shovsepy          #+#    #+#             */
/*   Updated: 2022/01/07 12:36:09 by shovsepy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	terminate(int exit_code)
{
	if (g_mini.cmd_count == 1)
	{
		if (!g_mini.status)
			exit(exit_code);
	}
	else
	{
		if (!exit_code)
			exit(g_mini.status);
		exit(exit_code);
	}
}

void	ft_exit(t_cmd *cmd)
{
	int	exit_code;

	g_mini.status = 0;
	exit_code = 0;
	if (g_mini.cmd_count == 1)
		ft_putstr_fd("exit 💚\n", STDERR);
	if (ft_matrixlen(cmd->args) == 1)
		exit(0);
	if (!ft_isnum(cmd->args[1]))
	{
		exit_code = 255;
		ft_minishell_error("minisell: exit: numeric argument required");
	}
	else
	{
		if (ft_matrixlen(cmd->args) == 2)
			exit_code = ft_atoi(cmd->args[1]);
		else
			g_mini.status = ft_minishell_error("minishell: too many args");
	}
	terminate(exit_code);
}
