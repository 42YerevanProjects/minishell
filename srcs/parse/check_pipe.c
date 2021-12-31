#include "../../includes/minishell.h"

/**
 * The functrion check for a valid pipe. If the pipe has second
 * part or it is not a double pipe it returns 1, 0 otherwise. 
 **/

static int	valid_pipe(int index)
{
	char *token;
	char *next;

	token = g_mini.tokens->token_array[index];
	next = g_mini.tokens->token_array[index + 1];
	if (token && !ft_strcmp(token, "|") && (next != NULL && ft_strcmp(next, "|")))
			return (1);
	return (0);
}

/**
 * The function checks for invalid pipe. If the pipe has no second
 * part (command | NULL) or it is a double pipe (`||`) it returns
 * 1, 0 otherwise.
 **/

static int	not_valid_pipe(int index)
{
	char	*token;
	char	*next;

	token = g_mini.tokens->token_array[index];
	next = g_mini.tokens->token_array[index + 1];
	if (token && !ft_strcmp(token, "|") && (next == NULL || !ft_strcmp(next, "|")))
		return (1);
	return (0);
}

/**
 * The function check for valid pipe. If the pipe is valid => it just
 * increments the index by passing to the next token. Else if the pipe
 * is not valid (it is a `||` or a pipe without second part) it outputs 
 * error.
 **/

int	check_pipe(char **args, int *index)
{
	if (valid_pipe(*index))
		*index = *index + 1;
	else if (not_valid_pipe(*index))
	{
		ft_minishell_error("minishell: syntax error: pipe");
		ft_free_matrix(args);
		g_mini.status = SYNTAX_ERROR;
		return (1);
	}
	return (0);
}
