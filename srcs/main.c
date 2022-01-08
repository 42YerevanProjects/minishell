/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shovsepy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:34:45 by shovsepy          #+#    #+#             */
/*   Updated: 2022/01/07 12:36:09 by shovsepy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_mini	g_mini;

int	main(int argc, char **argv, char **env)
{
	char	*line;

	(void) argc;
	(void) argv;
	init(&g_mini, env);
	sig_init();
	while (1)
	{
		line = readline("minishell ▸ ");
		if (!line)
		{
			ft_putstr_fd("minishell: exit 💚\n", STDERR);
			return (SUCCESS);
		}
		parse_and_execute(line);
		if (ft_strcmp(line, ""))
			add_history(line);
		free(line);
	}
	return (SUCCESS);
}
