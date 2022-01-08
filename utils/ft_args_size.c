/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalaban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:46:34 by abalaban          #+#    #+#             */
/*   Updated: 2022/01/07 12:46:12 by abalaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_args_size(int index)
{
	int		size;

	size = 0;
	while (g_mini.tokens->token_array[index]
		&& ft_strcmp(g_mini.tokens->token_array[index], "|"))
	{
		size++;
		index++;
	}
	return (size + 1);
}
