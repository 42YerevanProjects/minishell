#include "../../includes/minishell.h"

/**
 * The function check for valid input with redirections. It check 
 * whether </>>/> is the last token in the command OR encountered an
 * unquoted redireciton operator after another one.
 **/

static int check_redirection(int index)
{
	char	*token;
	char	*quote;

	token = g_mini.tokens->token_array[index];
	quote = g_mini.tokens->quote_array[index];
	if (token == NULL || (token[0] == '|' && token[1] == '\0')
			|| (quote && !*quote && (!ft_strcmp(token, "<<") || !ft_strcmp(token, ">>")
					|| !ft_strcmp(token, "<") || !ft_strcmp(token, ">"))))
		return (1);
	return (0);
}

/**
 * The function deals with redirection. It check for valid input with
 * redirection and updates file descriptors of the command appropriately.
 * It also creates the file required by redirections.
 **/

static int	treat_redirection(int *cmd_fd, int *index, int open_flag)
{
	int		fd;		// fd for the file to be created
	char	dir;	// variable for a chek

	/* Taking the first character of the token (> or <)*/
	dir = g_mini.tokens->token_array[*index][0];
	*index = *index + 1;

	/* Error handling */
	if (check_redirection(*index))
	{
		ft_minishell_error("minishell: syntax error: redirection");
		g_mini.status = SYNTAX_ERROR;
		return (1);
	}
	/* If the command used a file previously, then close it */
	if ((dir == '>' && *cmd_fd != 1) || (dir == '<' && *cmd_fd != 0))
		close(*cmd_fd);
	/* Create or open the file specified */
	fd = open(g_mini.tokens->token_array[*index], open_flag, 0644);
	if (fd == -1)
	{
		perror("minishell: Faild to open a file");
		g_mini.status = 1;
		return (1);
	}
	/* Assign the file's descriptor to command's appropriate field */
	*cmd_fd = fd;
	return (0);
}

/**
 * The function takes the token and analyses it. If it is a redirection, it 
 * treates the token accordingly, else if it is an argument the function adds it
 * to the args variable. The function returns 0 on success, 1 otherwie.
 **/

static int	treat_token(t_cmd *cmd, char ***args, int *index, int *p)
{
	int		err;
	char	*token;

	err = 0;
	token = g_mini.tokens->token_array[*index];
//	TODO: Add the heredoc case
//	if (!ft_strcmp( "<<"))
//		err = treat_heredoc(cmd, index);
	if (!ft_strcmp(token, ">"))
		err = treat_redirection(&(cmd->out), index, O_TRUNC | O_WRONLY | O_CREAT);
	else if (!ft_strcmp(token, ">>"))
		err = treat_redirection(&(cmd->out), index, O_APPEND | O_WRONLY | O_CREAT);
	else if (!ft_strcmp(token, "<"))
		err = treat_redirection(&(cmd->in), index, O_RDONLY);
	else
	{
		(*args)[*p] = ft_strdup(token);
		*p = *p + 1;
	}
	return (err);
}

/**
 * The function extracts the arguments for a command. Allocates memory
 * for that command and initializes appropriate field of cmd. It also
 * deal with redirections and check for valid input. Notice that it keeps
 * tract of tokens with the help of index refference. The function returns
 * 0 on success, 1 otherwise. 
 **/

int	extract_argument(t_cmd *cmd, int *index)
{
	char	**args;
	int		p;		// to keep track of free indicis in args

	/* Allocating appropriate memory for args */
	args = ft_calloc(ft_args_size(*index), sizeof(char *));
	p = 0;
	/* Extract the arguments for a command till a pipe `|` */
	while (g_mini.tokens->token_array[*index] && ft_strcmp(g_mini.tokens->token_array[*index], "|" ))
	{
		/* Trating each token separatly */
		if (treat_token(cmd, &args, index, &p))
		{
			/* If something goes wrong */
			ft_free_matrix(args);
			return (1);
		}
		/* preceding to next token */
		*index = *index + 1;
	}
	/* check weather | is valid: has second parts after it or is not a `||` */
	if (check_pipe(args, index))
		return (1);
	/* If arry of arguments is not empty add it to the appropriate field in cmd */
	if (ft_matrixlen(args) > 0)
	{	
		cmd->args = ft_array_copy(args);
		ft_free_matrix(args);
	}
	return (0);
}
