/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalaban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:46:34 by abalaban          #+#    #+#             */
/*   Updated: 2022/01/07 12:46:12 by abalaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_with_option_n(char **args)
{
	int	i;

	i = 1;
	if (ft_strlen(args[1]) < 2 || args[1][0] != '-' || args[1][1] != 'n')
		return (0);
	while (args[1][i])
	{
		if (args[1][i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_cmd *cmd)
{
	int	opt_flag;
	int	i;

	opt_flag = is_with_option_n(cmd->args);
	if (opt_flag)
		i = 2;
	else
		i = 1;
	if (!cmd->args[i])
	{
		if (!opt_flag)
			ft_putstr_fd("\n", cmd->out);
		return (0);
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], cmd->out);
		i++;
		if (cmd->args[i])
			ft_putstr_fd(" ", cmd->out);
	}
	if (!opt_flag)
		ft_putstr_fd("\n", cmd->out);
	return (0);
}
