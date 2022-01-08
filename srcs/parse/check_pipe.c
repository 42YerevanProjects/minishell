/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shovsepy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:34:45 by shovsepy          #+#    #+#             */
/*   Updated: 2022/01/07 12:36:09 by shovsepy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	valid_pipe(int index)
{
	char	*token;
	char	*next;

	token = g_mini.tokens->token_array[index];
	next = g_mini.tokens->token_array[index + 1];
	if (token && !ft_strcmp(token, "|")
		&& (next != NULL && ft_strcmp(next, "|")))
		return (1);
	return (0);
}

static int	not_valid_pipe(int index)
{
	char	*token;
	char	*next;

	token = g_mini.tokens->token_array[index];
	next = g_mini.tokens->token_array[index + 1];
	if (token && !ft_strcmp(token, "|")
		&& (next == NULL || !ft_strcmp(next, "|")))
		return (1);
	return (0);
}

int	check_pipe(char **args, int *index)
{
	if (valid_pipe(*index))
		*index = *index + 1;
	else if (not_valid_pipe(*index))
	{
		ft_minishell_error("minishell: syntax error: pipe");
		ft_free_matrix(args);
		g_mini.status = SYNTAX_ERROR;
		return (1);
	}
	return (0);
}
