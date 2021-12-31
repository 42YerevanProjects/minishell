#include "../includes/minishell.h"

void	ft_free_matrix(char **matrix)
{
	int i;

	i = 0;
	while (matrix[i])
		ft_memdel(matrix[i++]);
	free(matrix);
	matrix = NULL;
}

void	ft_free_commands(t_cmd *cmds)
{
	int	i;

	i = 0;
	if (cmds)
	{
		while (i < g_mini.cmd_count)
		{
			if (cmds[i].in != 0 && cmds[i].in != 1)
				close(cmds[i].in);
			if (cmds[i].out != 1 && cmds[i].out != 0)
				close(cmds[i].out);
			if (cmds[i].heredoc)
				ft_free_matrix(cmds[i].heredoc);
			if (cmds[i].refine)
				ft_free_matrix(cmds[i].refine);
			if (cmds[i].args)
				ft_free_matrix(cmds[i].args);
			i++;
		}
		free(cmds);
		cmds = NULL;
	}
}

void	ft_free_tokens(t_token *tokens)
{
	if (tokens)
	{
		if (tokens->token_array)
			ft_free_matrix(tokens->token_array);
		if (tokens->quote_array)
			ft_free_matrix(tokens->quote_array);
		free(tokens);
	}
}
