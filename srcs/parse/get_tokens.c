#include "../../includes/minishell.h"

/**
 * The function allocates memory for token_array and quote_array fields
 * of token struct and initializes the array size to 0.
 **/

static void	init_token_array(char *line)
{
	int	num;

	num = ft_token_num(line) + 1;
	g_mini.tokens->size = 0;
	g_mini.tokens->token_array = (char **)malloc(sizeof(char *) * num);
	g_mini.tokens->quote_array = (char **)malloc(sizeof(char *) * num);
}

/**
 * The function adds the token and quote to the token_array and
 * quote_array of the tokens field in g_mini.
 **/

static void	add_token_array(char *token, char* quote)
{
	int	index;

	index = g_mini.tokens->size;
	g_mini.tokens->token_array[index] = token;
	g_mini.tokens->quote_array[index] = quote;
	g_mini.tokens->size++;
}


/**
 * The function takes a line as an argument and tokenizes it.
 * It also deals with expansions and memory allocations.
 **/

void	get_tokens(char *line)
{
	int			i;
	char		*token;									// temp var to store a token
	char		*quote;									// temp var to store a quoted token

	i = 0;
	g_mini.tokens = ft_calloc(1, sizeof(t_token));
	if (line)
		init_token_array(line);
	else
		return ;
	/* Iterate over line and extracts tokens */
	while (line[i])
	{
		/* extracts a token and returns index of next word */
		i += extract_token(&line[i], &token, &quote);
		/* if we got token and quote add them to appropriate arrays */
		if (token != NULL && quote != NULL)
			add_token_array(token, quote);
	}
	/* Terminate arrays with NULLs */
	add_token_array(NULL, NULL);
}
