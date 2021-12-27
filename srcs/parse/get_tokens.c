#include "../../includes/minishell.h"

/**
 * The function takes a line as an argument and tokenizes it.
 * It also deals with expansions and memory allocations.
 **/

void	get_tokens(char *line)
{
	int			i;
	int			num;									// var to store max # of tokens
	char		*token;									// temp var to store a token
	char		*quote;									// temp var to store a quoted token

	i = 0;
	num = token_num(line);
	g_mini.tokens = ft_calloc(1, sizeof(t_token));
	if (line)
	{
		g_mini.tokens->token_array = (char **)malloc(sizeof(char *) * num);
		g_mini.tokens->quote_array = (char **)malloc(sizeof(char *) * num);
	}
	else
		return ;
	/* Iterate over line and extracts tokens */
	while (line[i])
	{
		i += extract_token(&line[i], &token, &quote);	// extracts a token and returns index of next word
		break ; 										// this is done for testing
	}
}
