#include "../../includes/minishell.h"

/**
 * The function initializes input and output streams of each command accordingly.
 **/

void	inint_io(void)
{
	int	i;

	i = 0;
	while (i < g_mini.cmd_count)
	{
		g_mini.commands[i].in = STDIN;
		g_mini.commands[i].out = STDOUT;
		g_mini.commands[i].args = extract_arguments(&g_mini.commands[i]);
	}
}


/**
 * The function initializes the commands array in the g_mini struct.
 **/

void	parse_commands(void)
{
	/* If there are no tokens just return */
	if (!g_mini.tokens || !g_mini.tokens->token_array)
		return ;
	g_mini.cmd_count = ft_count_commands(g_mini.tokens->token_array);
	g_mini.commands = ft_calloc(g_mini.cmd_count, sizeof(t_cmd));
	/* if the first character is the pipe '|' */
	if (!ft_strcmp(token[0], "|"))
	{
		ft_minishell_error("minishell: parse error near `|'");
		g_data.status = PARSE_ERROR;
		free(commands);
		return ;
	}
	init_io();
}
