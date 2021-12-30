#include "../../includes/minishell.h"


/**
 * The function initializes input and output streams of pipes.
 **/

static void	init_pipe(int i)
{
	int		pipefd[2];

	/* Creating a pipe */
	pipe(pipefd);
	/* If the previous command uses a file as out close the pipe out*/
	if (g_mini.commands[i - 1].out != 1)
		close(pipefd[1]);
	/* Else previous command writes to the pipe */
	else
		g_mini.commands[i - 1].out = pipefd[1];
	/* If the current command uses a file as in close the pipe in */
	if (g_mini.commands[i].in != 0)
		close(pipefd[0]);
	/* Else current command reads from pipe */
	else
		g_mini.commands[i].in = pipefd[0];
}



/**
 * The function initializes input and output streams of each command accordingly.
 * It then initializes the args of each command with the help of extract_argument
 * function. In case of any error during extracting it just frees commands array and
 * returns.
 **/

static void	init_commands_and_io(void)
{
	int	i;		// to iterate over commands
	int	index;	// to iterate over tokens array

	i = 0;
	index = 0;
	/* Initializing each command */
	while (i < g_mini.cmd_count)
	{
		g_mini.commands[i].in = STDIN;
		g_mini.commands[i].out = STDOUT;
		/* If something bad happened while extracting */
		if(extract_argument(&g_mini.commands[i], &index))
		{
			ft_free_commands(g_mini.commands);
			return ;
		}
		/* Initialize pipe discripters except the first command */
		if (i)
			init_pipe(i);
		i++;
	}
}


/**
 * The function initializes the commands array in the g_mini struct.
 * It also initializes the I/O streams and args field of each command.
 **/

void	parse_commands(void)
{
	/* If there are no tokens just return */
	if (!g_mini.tokens || !g_mini.tokens->token_array)
		return ;
	/* Taking the command count and initializing the commands array*/
	g_mini.cmd_count = ft_count_commands(g_mini.tokens->token_array);
	g_mini.commands = ft_calloc(g_mini.cmd_count, sizeof(t_cmd));
	/* If the first character is the pipe '|' */
	if (!ft_strcmp(g_mini.tokens->token_array[0], "|"))
	{
		ft_minishell_error("minishell: syntax error near `|'");
		g_mini.status = SYNTAX_ERROR;
		free(g_mini.commands);
		return ;
	}
	/* Initializing I/O streams and args */
	init_commands_and_io();
}
