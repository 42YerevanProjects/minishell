/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shovsepy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:34:45 by shovsepy          #+#    #+#             */
/*   Updated: 2022/01/07 12:36:09 by shovsepy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_getenv_full(const char *var)
{
	t_env	*head;
	int		var_len;
	char	*identifier;

	head = g_mini.env;
	identifier = ft_separate_identifier((char *) var);
	var_len = ft_strlen(identifier);
	if (!ft_is_valid_identifier(identifier))
	{
		free(identifier);
		return (NULL);
	}
	while (head != NULL)
	{
		if (!ft_strncmp(head->value, identifier, var_len)
			&& (head->value[var_len] == '='
				|| head->value[var_len] == '\0'))
		{
			free(identifier);
			return (head->value);
		}
		head = head->next;
	}
	free(identifier);
	return (NULL);
}

char	*ft_getenv(char *var)
{
	char	*env;

	env = ft_getenv_full(var);
	if (env)
		return (env + ft_strlen(var) + 1);
	return (NULL);
}
