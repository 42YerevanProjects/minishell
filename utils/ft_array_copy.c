/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalaban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:46:34 by abalaban          #+#    #+#             */
/*   Updated: 2022/01/07 12:46:12 by abalaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_array_copy(char **args)
{
	char	**copy;
	int		i;

	i = ft_matrixlen(args) + 1;
	copy = (char **)malloc(sizeof(char *) * i);
	i = 0;
	while (args[i])
	{
		copy[i] = ft_strdup(args[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
