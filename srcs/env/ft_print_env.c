/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalaban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:46:34 by abalaban          #+#    #+#             */
/*   Updated: 2022/01/07 12:46:12 by abalaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_env(int fd)
{
	t_env	*head;
	int		i;

	head = g_mini.env;
	while (head)
	{
		i = 0;
		ft_putstr_fd("declare -x ", fd);
		while (head->value[i] && head->value[i] != '=')
			ft_putchar_fd(head->value[i++], fd);
		ft_putstr_fd("=\"", fd);
		i++;
		while (head->value[i])
			ft_putchar_fd(head->value[i++], fd);
		ft_putstr_fd("\"\n", fd);
		head = head->next;
	}
}
