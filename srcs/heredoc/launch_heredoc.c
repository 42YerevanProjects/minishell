/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shovsepy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:34:45 by shovsepy          #+#    #+#             */
/*   Updated: 2022/01/07 12:36:09 by shovsepy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_write_end(t_heredoc *h_info, int i, int *j)
{
	int	pipefd[2];

	if (g_mini.commands[i].heredoc)
	{
		pipe(pipefd);
		if (g_mini.commands[i].in != 0)
			close(g_mini.commands[i].in);
		g_mini.commands[i].in = pipefd[0];
		h_info->w_ends[(*j)++] = pipefd[1];
	}
}

static int	save_write_ends(t_heredoc *h_info)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (i < g_mini.cmd_count)
		if (g_mini.commands[i++].heredoc)
			count++;
	h_info->w_ends = malloc(count * sizeof(int *));
	i = 0;
	while (i < g_mini.cmd_count)
	{
		init_write_end(h_info, i, &j);
		i++;
	}
	return (count);
}

static int	init_heredoc_info(t_heredoc *h_info)
{
	int	i;

	h_info->w_ends = NULL;
	h_info->heredocs = save_write_ends(h_info);
	if (!h_info->w_ends)
		return (1);
	sig_ignore();
	h_info->h_pid = fork();
	i = 0;
	while (h_info->h_pid && i < h_info->heredocs)
		close(h_info->w_ends[i++]);
	h_info->heredocs = 0;
	return (0);
}

int	launch_heredoc(void)
{
	t_heredoc	h_info;

	if (init_heredoc_info(&h_info))
		return (0);
	if (h_info.h_pid == 0)
		process_heredoc(&h_info);
	wait(&(h_info.h_status));
	free(h_info.w_ends);
	sig_init();
	if (WEXITSTATUS(h_info.h_status) == 1)
	{
		g_mini.status = 130;
		ft_putstr_fd("\n", STDOUT);
		return (1);
	}
	return (0);
}
