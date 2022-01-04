#include "../../includes/minishell.h"

/**
 * The function reads from a heredoc. Returns 1 if the delimeter inputed
 * or the prompt returned null, oterwise 0 is returned.
 **/
static int	read_heredoc(t_heredoc *h_info, t_cmd *cmd)
{
	char	*h_line;
	int		k;

	/* Take the index of the right write end */
	k = h_info->heredocs;
	h_line = readline("> ");
	if (h_line == NULL)
		return (1);
	/* If the delimeter achieved close the end and break */
	else if (!ft_strcmp(h_line, h_info->heredoc))
	{
		free(h_line);
		if (h_info->j == ft_matrixlen(cmd->heredoc))
			close(h_info->w_ends[k]);
		return (1);
	}
	/* If the line needs to be refined, refine it */
	if (h_info->refined)
		h_line = ft_refine_line(h_line);
	/* Output the heredoc information */
	if (h_info->j == ft_matrixlen(cmd->heredoc))
	{
		ft_putstr_fd(h_line, h_info->w_ends[k]);
		ft_putstr_fd("\n", h_info->w_ends[k]);
	}
	free(h_line);
	return (0);
}

/**
 * The function recieves each heredoc and reads input from it.
 **/

static void	recieve_heredoc(t_heredoc *h_info, t_cmd *cmd)
{
	int	br;

	if (cmd->heredoc)
	{
		h_info->j = 0;
		/* As long as there is smth to read */
		while (h_info->j < ft_matrixlen(cmd->heredoc))
		{
			/* Check weather the line needs to be refined */
			h_info->refined = 1;
			if (!ft_strcmp(cmd->refine[h_info->j], "\'")
				&& h_info->j == ft_matrixlen(cmd->heredoc) - 1)
				h_info->refined = 0;
			/* Take a word from the command heredoc */
			h_info->heredoc = cmd->heredoc[h_info->j];
			h_info->j++;
			/* Read from heredoc til the process is interrupted or braked */
			while (1)
			{
				br = read_heredoc(h_info, cmd);
				/* If the delimeter is read or interrupted */
				if (br)
					break ;
			}
		}
	}
}

/**
 * The function is run in the child process. It recieves all the
 * heredocs.
 **/

void	process_heredoc(t_heredoc *h_info)
{
	int	i;

	i = 0;
	/* Define signals for heredoc process */
	sig_heredoc();
	/* Recieve heredoc for each command */
	while (i < g_mini.cmd_count)
	{
		/* If the command contains a heredoc recieve it*/
		if (g_mini.commands[i].heredoc)
			recieve_heredoc(h_info, &g_mini.commands[i]);
		h_info->heredocs++;
		i++;
	}
	/* Exit the process after rcieving all the heredocs */
	exit(0);
}

