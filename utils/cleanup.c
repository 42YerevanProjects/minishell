/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shovsepy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:34:45 by shovsepy          #+#    #+#             */
/*   Updated: 2022/01/07 12:36:09 by shovsepy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix && matrix[i])
	{
		free(matrix[i]);
		matrix[i++] = NULL;
	}
	if (matrix)
		free(matrix);
	matrix = NULL;
}

void	ft_free_commands(t_cmd *cmds)
{
	int	i;

	i = 0;
	if (cmds)
	{
		while (i < g_mini.cmd_count)
		{
			if (cmds[i].in != 0 && cmds[i].in != 1)
				close(cmds[i].in);
			if (cmds[i].out != 1 && cmds[i].out != 0)
				close(cmds[i].out);
			if (cmds[i].heredoc)
				ft_free_matrix(cmds[i].heredoc);
			if (cmds[i].refine)
				ft_free_matrix(cmds[i].refine);
			if (cmds[i].args)
				ft_free_matrix(cmds[i].args);
			i++;
		}
		free(cmds);
		g_mini.commands = NULL;
	}
}

void	ft_free_tokens(void)
{
	if (g_mini.tokens)
	{
		if (g_mini.tokens->token_array)
			ft_free_matrix(g_mini.tokens->token_array);
		if (g_mini.tokens->quote_array)
			ft_free_matrix(g_mini.tokens->quote_array);
		free(g_mini.tokens);
	}
}

void	ft_free_fam(void)
{
	if (g_mini.fam)
	{
		free(g_mini.fam);
		g_mini.fam = NULL;
	}
}
