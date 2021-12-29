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
			exp->j += 2;
		ft_append_token(token, &line[exp->i], exp->j - exp->i, exp->expand);
		return (exp->j);
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
 * The functions processes a quote that has been encountered. The function
 * returns 1 if closing quote has been encountered, 0 otherwise.
 **/

static int	process_token_quote(char *line, char **token, char **quote, t_expansion *exp)
{
	char	*tmp;	//

	/* Try to find the closing quote */
	tmp = ft_strchr(&line[exp->j + 1], line[exp->j]);
	if (tmp)
	{
		if (!**quote)
			ft_append_token(quote, "\'", 1, 0);
		/* Add the everything before the quotes to the token */
		ft_append_token(token, &line[exp->i], exp->j - exp->i, exp->expand);
		exp->i = exp->j + 1;		// Update the start index to the character after opening quote
		exp->j = (tmp - 1) - line;	// Go to the closing quote  
		/* No need for expansion if single quotes */
		if (line[exp->j + 1] == '\'')
			exp->expand = 0;
		/* Append the word in quotes */
		ft_append_token(token, &line[exp->i], exp->j - exp->i + 1, exp->expand);
		exp->expand = 1;		// Reset expansion flag
		exp->i = exp->j + 2;	// Update starting index to point after closing quote
		exp->j = exp->i;		
		return (1);
	}
	return (0);
}

/**
 * The functions checks the character and decides what to do with it. The
 * function also treats opening and closing quotes. Function returns 1 if
 * quote has been encountered, 0 otherwise
 **/

static int	process_token_char(char *line, char **token, char **quote, t_expansion *exp)
{
	int		ret;

	/* If character is a normal character (no quotes) */
	if (line[exp->j] != '\'' && line[exp->j] != '\"'
		&& !ft_isspace(line[exp->j + 1]) && line[exp->j + 1])
			;
	/* If it is a closing quote */
	else if ((ft_isspace(line[exp->j + 1]) && !(line[exp->j] == '\''
				|| line[exp->j] == '\"')) || !line[exp->j + 1])
		ft_append_token(token, &line[exp->i], exp->j - exp->i + 1, exp->expand);
	/* If it is an openning quote */
	else
	{
		ret = process_token_quote(line, token, quote, exp);
		if (ret)
			return (1);
	}
	return (0);
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
	int			cont;									// stores the status after processing a char

	token_init(line, token, quote, &exp);				// initializes token, quote and exp
	/* Iterates over the characters of the given word */
	while (!ft_isspace(line[exp.j]) && line[exp.j])
	{
		/* If the character is a redirection or pipei, append to token and stop */
		if (line[exp.j] == '<' || line[exp.j] == '>' || line[exp.j] == '|')
			return (treat_pipe_and_redirection(line, token, &exp));
		/*  Else check for quote characters */
		cont = process_token_char(line, token, quote, &exp);
		/* If quotes has been encountered then exp.j has been updated */
		if (cont)
			continue ;
		exp.j++;		
	}
	return (exp.j);
}

