/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shovsepy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:34:45 by shovsepy          #+#    #+#             */
/*   Updated: 2022/01/07 12:36:09 by shovsepy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_pipe(int i)
{
	int		pipefd[2];

	pipe(pipefd);
	if (g_mini.commands[i - 1].out != 1)
		close(pipefd[1]);
	else
		g_mini.commands[i - 1].out = pipefd[1];
	if (g_mini.commands[i].in != 0)
		close(pipefd[0]);
	else
		g_mini.commands[i].in = pipefd[0];
}

static void	init_commands_and_io(void)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (i < g_mini.cmd_count)
	{
		g_mini.commands[i].in = STDIN;
		g_mini.commands[i].out = STDOUT;
		g_mini.commands[i].s = 0;
		if (extract_argument(&g_mini.commands[i], &index))
		{
			ft_free_commands(g_mini.commands);
			return ;
		}
		if (i)
			init_pipe(i);
		i++;
	}
}

void	parse_commands(void)
{
	if (!g_mini.tokens || !g_mini.tokens->token_array)
		return ;
	g_mini.cmd_count = ft_count_commands(g_mini.tokens->token_array);
	g_mini.commands = ft_calloc(g_mini.cmd_count, sizeof(t_cmd));
	if (!ft_strcmp(g_mini.tokens->token_array[0], "|"))
	{
		ft_minishell_error("minishell: syntax error near `|'");
		g_mini.status = SYNTAX_ERROR;
		ft_free_commands(g_mini.commands);
		return ;
	}
	init_commands_and_io();
}
