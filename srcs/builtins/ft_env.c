/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_enc.c	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalaban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:46:34 by abalaban          #+#    #+#             */
/*   Updated: 2022/01/07 12:46:12 by abalaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_cmd *cmd)
{
	t_env	*head;

	head = g_mini.env;
	if (ft_matrixlen(cmd->args) > 1)
	{
		ft_minishell_error("minishell: env: Too many args to env");
		return (1);
	}
	while (head)
	{
		ft_putstr_fd(head->value, cmd->out);
		ft_putstr_fd("\n", cmd->out);
		head = head->next;
	}
	return (0);
}
