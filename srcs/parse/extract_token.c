#include "../../includes/minishell.h"

static void	token_init(t_mini *mini, char *line, t_expansion *exp)
{
	int	num;

	exp->i = 0;
	exp->j = 0;
	exp->expand = 1;
	num = token_num(line);
	while (ft_isspace(line[exp->j]))
	{
		exp->i++;
		exp->j++;
	}
	if (line[exp->j])
	{
		mini->tokens->token_array = (char **)malloc(sizeof(char *) * num);
		mini->tokens->quote_array = (char **)malloc(sizeof(char *) * num);
	}
	else
	{
		mini->tokens->token_array = NULL;
		mini->tokens->quote_array = NULL;
	}
}


int	extract_token(t_mini *mini, char *line)
{
	t_expansion	exp;

	token_init(mini, line, &exp);
	while (!ft_isspace(line[exp.j]) && line[exp.j])
	{
		// TODO: Deal with pipes and redirections
		return 0; // this is done for testing. 
	}
	return (exp.j);
}
