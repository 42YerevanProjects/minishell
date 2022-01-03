#include "../../includes/minishell.h"

/**
 * Initializes a write_end by setting STDIN and STDOUT aprropriately.
 **/
static void	init_write_end(t_heredoc *h_info, int i, int *j)
{
	int	pipefd[2];

	if (g_mini.commands[i].heredoc)
	{
		pipe(pipefd);
		/* If the command used a file, close it */
		if (g_mini.commands[i].in != 0)
			close(g_mini.commands[i].in);
		/* Now command reads from an end of a pipe and writes to another one */
		g_mini.commands[i].in = pipefd[0];
		/* Save the write end in the w_ends array */
		h_info->w_ends[(*j)++] = pipefd[1];
	}
}

/**
 * The function counts the number of heredocs and allocates memory for 
 * w_ends array. It also initializes the write end of each command for heredoc.
 * Returns the number of heredocs.
 **/

static int	save_write_ends(t_heredoc *h_info)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	/* Count the heredocs and allocate memory for write ends */
	while (i < g_mini.cmd_count)
		if (g_mini.commands[i++].heredoc)
			count++;
	h_info->w_ends = malloc(count * sizeof(int *));
	i = 0;
	/* Save each write end */
	while (i < g_mini.cmd_count)
	{
		init_write_end(h_info, i, &j);
		i++;
	}
	return (count);
}

/**
 * The function initializes the information struct for heredoc 
 * processing. Returns 0 on success, 1 if we have no w_ends array.
 **/

static int	init_heredoc_info(t_heredoc *h_info)
{
	int	i;

	/* Initializing w_ends and counting heredocs */
	h_info->w_ends = NULL;
	h_info->heredocs = save_write_ends(h_info);
	if (!h_info->w_ends)
		return (1);
	/* Ignoring signals from a child process */
	sig_ignore();
	/* Creating a process for heredocs */
	h_info->h_pid = fork();
	/* Close cloned ends for parent process */
	i = 0;
	while (h_info->h_pid && i < h_info->heredocs)
		close(h_info->w_ends[i++]);
	h_info->heredocs = 0;
	return (0);
}

/**
 * The function launches a process for heredoc. Returns
 * 0 on success, 1 if it was terminated by SIGINT.
 **/

int	launch_heredoc(void)
{
	t_heredoc	h_info;

	if (init_heredoc_info(&h_info))
		return (0);
	/* Treat the child process */
	if (h_info.h_pid == 0)
		process_heredoc(&h_info);
	/* Wait for the heredoc process to return and take the status */
	wait(&(h_info.h_status));
	/* Free the w_ends array */
	free(h_info.w_ends);
	/* Define the normal signals for minishell */
	sig_init();
	/* If the heredoc was interrupted, update the status accordingly */
	if (WEXITSTATUS(h_info.h_status) == 1)
	{
		g_mini.status = 1;
		ft_putstr_fd("\n", STDOUT);
		return (1);
	}
	return (0);
}
