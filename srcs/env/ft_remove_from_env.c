/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_from_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shovsepy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:34:45 by shovsepy          #+#    #+#             */
/*   Updated: 2022/01/07 12:36:09 by shovsepy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_remove_from_env(char *var)
{
	t_env	*head;
	t_env	*prev;

	head = g_mini.env;
	prev = NULL;
	while (head)
	{
		if (!ft_strcmp(ft_separate_identifier(head->value),
				ft_separate_identifier(var)))
		{
			if (prev == NULL)
				g_mini.env = head->next;
			else
				prev->next = head->next;
			head->next = NULL;
			head = NULL;
			break ;
		}
		prev = head;
		head = head->next;
	}
}
