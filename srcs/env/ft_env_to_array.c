/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalaban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:46:34 by abalaban          #+#    #+#             */
/*   Updated: 2022/01/07 12:46:12 by abalaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_env_to_array(t_env *env)
{
	t_env	*head;
	char	**array;
	int		i;

	head = env;
	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	array = (char **)malloc(sizeof(char *) * i + 1);
	head = env;
	i = 0;
	while (head)
	{
		array[i++] = head->value;
		head = head->next;
	}
	array[i] = NULL;
	return (array);
}
