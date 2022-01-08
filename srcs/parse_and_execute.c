/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shovsepy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:35:45 by shovsepy          #+#    #+#             */
/*   Updated: 2022/01/07 12:36:09 by shovsepy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_update_status(int terminated, int wstatus)
{
	int		signaled;
	t_cmd	*selected;

	signaled = 0;
	if (terminated == g_mini.fam[g_mini.cmd_count - 1])
	{
		if (!WTERMSIG(wstatus))
			g_mini.status = WEXITSTATUS(wstatus);
		else
		{
			signaled = 1;
			g_mini.status = WTERMSIG(wstatus) + 128;
		}
	}
	selected = ft_find_command(terminated);
	if (selected)
	{
		if (selected->out != 1)
			close(selected->out);
		if (selected->in != 0)
			close(selected->in);
	}
	return (signaled);
}

static void	block_main_process(void)
{
	int	i;
	int	wstatus;
	int	signaled;

	i = 0;
	signaled = 0;
	while (i < g_mini.cmd_count)
	{
		signaled += ft_update_status(wait(&wstatus), wstatus);
		i++;
	}
	if (signaled)
	{
		if (g_mini.status == 131)
			ft_putstr_fd("Quit", STDOUT);
		ft_putstr_fd("\n", STDOUT);
	}
}

static void	launch_processes(void)
{
	int	i;

	if (g_mini.cmd_count == 1 && g_mini.commands[0].args
		&& ft_convert_builtin(g_mini.commands[0].args[0]))
		ft_exec(&g_mini.commands[0]);
	else
	{
		i = 0;
		while (i < g_mini.cmd_count)
		{
			g_mini.fam[i] = fork();
			if (g_mini.fam[i] == 0)
			{
				if (!g_mini.commands[i].args)
					exit(0);
				sig_default();
				ft_exec(&g_mini.commands[i]);
			}
			i++;
		}
		sig_ignore();
		block_main_process();
		sig_init();
	}
}

void	parse_and_execute(char *line)
{
	get_tokens(line);
	if (!g_mini.tokens->token_array || !g_mini.tokens->token_array[0])
	{
		ft_free_tokens();
		return ;
	}
	parse_commands();
	if (!g_mini.commands || launch_heredoc())
	{
		ft_free_tokens();
		ft_free_commands(g_mini.commands);
		return ;
	}
	g_mini.fam = ft_calloc(g_mini.cmd_count, sizeof(pid_t));
	launch_processes();
	ft_free_commands(g_mini.commands);
	ft_free_fam();
	ft_free_tokens();
}
