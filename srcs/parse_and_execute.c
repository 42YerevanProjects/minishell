#include "../includes/minishell.h"


static int	ft_update_status(int terminated, int returned)
{
	int		signaled;
	t_cmd	*selected;

	signaled = 0;
	if (terminated == g_mini.fam[g_mini.cmd_count - 1])
	{
		if (!WTERMSIG(returned))
			g_mini.status = WEXITSTATUS(returned);
		else
		{
			signaled = 1;
			g_mini.status = WTERMSIG(returned) + 128;
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
	int		i;
	int		returned;
	int		signaled;

	signaled = 0;
	i = 0;
	while (i < g_mini.cmd_count)
	{
		signaled += ft_update_status(wait(&returned), returned);
		i++;
	}
	if (signaled)
	{
		if (g_mini.status == 131)
			ft_putstr_fd("Quit: 3", 1);
		ft_putstr_fd("\n", 1);
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
	if (!g_mini.tokens->token_array)
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
