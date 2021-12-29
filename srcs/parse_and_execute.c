#include "../includes/minishell.h"

/**
 * The function is supposed to parse the input and execute the commands.
 **/

void	parse_and_execute(char *line)
{
	/* initializes the tokens of struct g_mini */
	get_tokens(line);
	/* If there are no tokens at all; do nothing */
	if (!g_mini.tokens->token_array)
		return ;
	/* Initializing the commands field in g_mini */
	parse_commands();
}
