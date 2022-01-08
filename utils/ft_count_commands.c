/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalaban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:46:34 by abalaban          #+#    #+#             */
/*   Updated: 2022/01/07 12:46:12 by abalaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_count_commands(char **token_array)
{
	int	i;
	int	c;

	if (!token_array)
		return (0);
	i = 0;
	c = 1;
	while (token_array[i])
	{
		if (token_array[i][0] == '|' && token_array[i][1] == '\0')
			c++;
		i++;
	}
	return (c);
}
