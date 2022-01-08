/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shovsepy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:34:45 by shovsepy          #+#    #+#             */
/*   Updated: 2022/01/07 12:36:09 by shovsepy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	read_heredoc(t_heredoc *h_info, t_cmd *cmd)
{
	char	*h_line;
	int		k;

	k = h_info->heredocs;
	h_line = readline("> ");
	if (h_line == NULL)
		return (1);
	else if (!ft_strcmp(h_line, h_info->heredoc))
	{
		free(h_line);
		if (h_info->j == ft_matrixlen(cmd->heredoc))
			close(h_info->w_ends[k]);
		return (1);
	}
	if (h_info->refined)
		h_line = ft_refine_line(h_line);
	if (h_info->j == ft_matrixlen(cmd->heredoc))
	{
		ft_putstr_fd(h_line, h_info->w_ends[k]);
		ft_putstr_fd("\n", h_info->w_ends[k]);
	}
	free(h_line);
	return (0);
}

static void	recieve_heredoc(t_heredoc *h_info, t_cmd *cmd)
{
	int	br;

	if (cmd->heredoc)
	{
		h_info->j = 0;
		while (h_info->j < ft_matrixlen(cmd->heredoc))
		{
			h_info->refined = 1;
			if (!ft_strcmp(cmd->refine[h_info->j], "\'")
				&& h_info->j == ft_matrixlen(cmd->heredoc) - 1)
				h_info->refined = 0;
			h_info->heredoc = cmd->heredoc[h_info->j];
			h_info->j++;
			while (1)
			{
				br = read_heredoc(h_info, cmd);
				if (br)
					break ;
			}
		}
	}
}

void	process_heredoc(t_heredoc *h_info)
{
	int	i;

	i = 0;
	sig_heredoc();
	while (i < g_mini.cmd_count)
	{
		if (g_mini.commands[i].heredoc)
			recieve_heredoc(h_info, &g_mini.commands[i]);
		h_info->heredocs++;
		i++;
	}
	exit(0);
}
