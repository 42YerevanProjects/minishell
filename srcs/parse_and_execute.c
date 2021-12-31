#include "../includes/minishell.h"


//static void	launch_processes(void)
//{
//	//TODO: Deal with this after builtins
//}


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
		ft_free_commands(g_mini.commands);
		ft_free_tokens(g_mini.tokens);
		return ;
	}
	/* If everything is ok allocate memory for process IDs */
	g_mini.fam = ft_calloc(g_mini.cmd_count, sizeof(pid_t));
//	launch_processes();
}
