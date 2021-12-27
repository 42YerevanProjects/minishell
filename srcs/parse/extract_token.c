#include "../../includes/minishell.h"

/**
 * The function treates the case when '<' '>' or '|' is encountered.
 **/

static int	treat_pipe_and_redirection(char *line, char **token, t_expansion *exp)
{
	/* If there is something to add to the token */
	if (exp->i != exp->j || (*token)[0] != '\0')
	{
		ft_append_token(token, &line[exp->i], exp->j - exp->i, exp->expand);
		return (exp->j);
	}
	/* If token is empty */
	else
	{
		if (!ft_strncmp(&line[exp->j], "<<", 2) || !ft_strncmp(&line[exp->j],
				">>", 2))
			exp->j++;
		ft_append_token(token, &line[exp->i], exp->j - exp->i + 1, exp->expand);
		return (exp->j + 1);
	}
}

/**
 * The function initializes the expansion struct, skips spaces and allocates
 * the token and quote pointers appropriately.
 *
 * exp->i -- index of the first char of the token
 * exp->j -- index of the current char of the token
 * exp->expand -- flag for expansion; 1 by default, 0 if single quotes encountered
 **/

static void	token_init(char *line, char **token, char **quote, t_expansion *exp)
{
	exp->i = 0;
	exp->j = 0;
	exp->expand = 1;
	while (ft_isspace(line[exp->j]))
	{
		exp->i++;
		exp->j++;
	}
	if (line[exp->j])
	{
		*token = ft_strdup("");
		*quote = ft_strdup("");
	}
	else
	{
		*token = NULL;
		*quote = NULL;
	}
}

/**
 * The function takes a line and refferences of token and quote variables.
 * It initializes the token and quote variables charachter by character appropriatly.
 * Deals with expansions, pipes and redirections. It initializes one token at a time.
 * Returns the index of the next non-whitespace character of the line.
 **/

int	extract_token(char *line, char **token, char **quote)
{
	t_expansion	exp;									// struct to help deal with expansions

	token_init(line, token, quote, &exp);				// initializes token, quote and exp
	/* Iterates over the characters of the given word */
	while (!ft_isspace(line[exp.j]) && line[exp.j])
	{
		/* If the character is a redirection or pipe append to token and stop */
		if (line[exp.j] == '<' || line[exp.j] == '>' || line[exp.j] == '|')
			return (treat_pipe_and_redirection(line, token, &exp));
		return 0;		
	}
	return (exp.j);
}

