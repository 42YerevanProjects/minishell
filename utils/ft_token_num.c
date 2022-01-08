/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_num.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalaban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:46:34 by abalaban          #+#    #+#             */
/*   Updated: 2022/01/07 12:46:12 by abalaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	add_len(char *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token[i])
	{
		if (token[i] == '|')
			count += 2;
		else if (token[i] == '>')
		{
			if (token[i + 1] && token[i + 1] == '>')
				i += 2;
			count += 2;
		}
		else if (token[i] == '<')
		{
			if (token[i + 1] && token[i + 1] == '<')
				i += 2;
			count += 2;
		}
		i++;
	}
	return (count + 1);
}

int	ft_token_num(char *line)
{
	char	**tokens;
	int		i;
	int		len;

	i = 0;
	len = 0;
	tokens = ft_split(line, ' ');
	while (tokens[i])
	{
		len += add_len(tokens[i]);
		i++;
	}
	ft_free_matrix(tokens);
	return (len);
}
