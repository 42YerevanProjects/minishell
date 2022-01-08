/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_argument.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shovsepy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:34:45 by shovsepy          #+#    #+#             */
/*   Updated: 2022/01/07 12:36:09 by shovsepy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	treat_heredoc(t_cmd *cmd, int *index)
{
	char	*token;
	char	*err;

	*index = *index + 1;
	token = g_mini.tokens->token_array[*index];
	if (token == NULL || (token[0] == '|' && token[1] == '\0')
		|| !ft_strcmp(token, "<<"))
	{
		if (token == NULL)
			err = "syntax error near unexpected token `newline'";
		else
			err = ft_strjoin3("syntax error near unexpected token `",
					token, "'");
		ft_minishell_error(ft_strjoin("minishell: ", err));
		g_mini.status = SYNTAX_ERROR;
		return (1);
	}
	if (!cmd->heredoc)
		ft_alloc_heredoc(cmd);
	cmd->heredoc[cmd->s] = ft_strdup(token);
	if (!cmd->refine)
		ft_alloc_refine(cmd);
	cmd->refine[cmd->s++] = ft_strdup(g_mini.tokens->quote_array[*index]);
	return (0);
}

static int	check_redirection(int index)
{
	char	*token;
	char	*quote;

	token = g_mini.tokens->token_array[index];
	quote = g_mini.tokens->quote_array[index];
	if (token == NULL || (token[0] == '|' && token[1] == '\0')
		|| (quote && !*quote && (!ft_strcmp(token, "<<")
				|| !ft_strcmp(token, ">>")
				|| !ft_strcmp(token, "<") || !ft_strcmp(token, ">"))))
		return (1);
	return (0);
}

static int	treat_redirection(int *cmd_fd, int *index, int open_flag)
{
	int		fd;
	char	dir;

	dir = g_mini.tokens->token_array[*index][0];
	*index = *index + 1;
	if (check_redirection(*index))
	{
		ft_minishell_error("minishell: syntax error: redirection");
		g_mini.status = SYNTAX_ERROR;
		return (1);
	}
	if ((dir == '>' && *cmd_fd != 1) || (dir == '<' && *cmd_fd != 0))
		close(*cmd_fd);
	fd = open(g_mini.tokens->token_array[*index], open_flag, 0644);
	if (fd == -1)
	{
		perror("minishell: Faild to open a file");
		g_mini.status = 1;
		return (1);
	}
	*cmd_fd = fd;
	return (0);
}

static int	treat_token(t_cmd *cmd, char ***args, int *index, int *p)
{
	int		err;
	char	*token;

	err = 0;
	token = g_mini.tokens->token_array[*index];
	if (!ft_strcmp(token, "<<"))
		err = treat_heredoc(cmd, index);
	else if (!ft_strcmp(token, ">"))
		err = treat_redirection(&(cmd->out), index,
				O_TRUNC | O_WRONLY | O_CREAT);
	else if (!ft_strcmp(token, ">>"))
		err = treat_redirection(&(cmd->out), index,
				O_APPEND | O_WRONLY | O_CREAT);
	else if (!ft_strcmp(token, "<"))
		err = treat_redirection(&(cmd->in), index, O_RDONLY);
	else
	{
		(*args)[*p] = ft_strdup(token);
		*p = *p + 1;
	}
	return (err);
}

int	extract_argument(t_cmd *cmd, int *index)
{
	char	**args;
	int		p;

	args = ft_calloc(ft_args_size(*index), sizeof(char *));
	p = 0;
	while (g_mini.tokens->token_array[*index]
		&& ft_strcmp(g_mini.tokens->token_array[*index], "|" ))
	{
		if (treat_token(cmd, &args, index, &p))
		{
			ft_free_matrix(args);
			return (1);
		}
		*index = *index + 1;
	}
	if (check_pipe(args, index))
		return (1);
	if (ft_matrixlen(args) > 0)
	{	
		cmd->args = ft_array_copy(args);
		ft_free_matrix(args);
	}
	return (0);
}
