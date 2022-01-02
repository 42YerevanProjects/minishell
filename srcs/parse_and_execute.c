#include "../includes/minishell.h"

/**
 * The function updates the status accordingly for each process.
 **/

static int	ft_update_status(int terminated, int wstatus)
{
	int		signaled;
	t_cmd	*selected;

	signaled = 0;
	/* If the terminated process is the last one */
	if (terminated == g_mini.fam[g_mini.cmd_count - 1])
	{
		/* If there is no termination signal, then take the status */
		if (!WTERMSIG(wstatus))
			g_mini.status = WEXITSTATUS(wstatus);
		/* Else if there is signal, update status */
		else
		{
			signaled = 1;
			g_mini.status = WTERMSIG(wstatus) + 128;
		}
	}
	/* Find the terminated command, and close related files */
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

/**
 * The function stops the main process until the child processes return.
 **/

static void	block_main_process(void)
{
	int	i;
	int	wstatus;
	int	signaled;

	/* No signals at first */
	i = 0;
	signaled = 0;
	/* Wait for each command and update status accordingly */
	while (i < g_mini.cmd_count)
	{
		signaled += ft_update_status(wait(&wstatus), wstatus);
		i++;
	}
	/* If a process signaled, check the status */
	if (signaled)
	{
		/* If the process status is not recoverable */
		if (g_mini.status == 131)
			ft_putstr_fd("Quit: 3", STDOUT);
		/* Else output a new line */
		ft_putstr_fd("\n", STDOUT);
	}
}

/**
 * The function launches the processes for commands and executes them. It 
 * also deals with waiting for processes and handles interprocess signals 
 * properly.
 **/

static void	launch_processes(void)
{
	int	i;

	/* If this is ust a builtin, no need to create a process */
	if (g_mini.cmd_count == 1 && g_mini.commands[0].args 
			&& ft_convert_builtin(g_mini.commands[0].args[0]))
		ft_exec(&g_mini.commands[0]);
	/* Else if there are more then 1 commands fork processes*/
	else
	{
		i = 0;
		/* Fork for each command */
		while (i < g_mini.cmd_count)
		{
			g_mini.fam[i] = fork();
			/* In the child process */
			if (g_mini.fam[i] == 0)
			{
				/* If no command to execute, exit the process */
				if (!g_mini.commands[i].args)
					exit(0);
				/* Otherwise update signals to default for the process */
				sig_default();
				/* Execute the command */
				ft_exec(&g_mini.commands[i]);
			}
			i++;
		}
		/* Ignore the signals came from the processes */
		sig_ignore();
		/* Block the main by waiting for the command processes to finish */
		block_main_process();
		/* Bring back the signals for minishell */
		sig_init();
	}
}


/**
 * The function is supposed to parse the input and execute the commands.
 **/

void	parse_and_execute(char *line)
{
	/* Initializes the tokens of struct g_mini */
	get_tokens(line);
	/* If there are no tokens at all; do nothing */
	if (!g_mini.tokens->token_array[0])
		return ;
	/* Initializing the commands field in g_mini */
	parse_commands();
	/* If there are no commands */
	if (!g_mini.commands)
	{
		ft_free_tokens();
		return ;
	}
	/* If everything is ok allocate memory for process IDs */
	g_mini.fam = ft_calloc(g_mini.cmd_count, sizeof(pid_t));
	/* Launch the processes and execute commands */
	launch_processes();
	/* Free the used memory after parsing and execution*/
	ft_free_commands(g_mini.commands);
	ft_free_fam();
	ft_free_tokens();
}
