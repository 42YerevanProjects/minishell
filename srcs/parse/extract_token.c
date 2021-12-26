#include "../../includes/minishell.h"

//static int	treat_pipe_and_redirection(char *line, char **token, t_expansion *exp)
//{
//	if (exp->i != exp->j || (*token)[0] != '\0')
//	{
//		
//	}
//}

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


int	extract_token(char *line, char **token, char **quote)
{
	t_expansion	exp;

	token_init(line, token, quote, &exp);
	while (!ft_isspace(line[exp.j]) && line[exp.j])
	{
//		if (line[exp.j] == '<' || line[exp.j] == '>' || line[exp.j] == '|')
//			return (treat_pipe_and_redirection(line, token, &exp));
		return 0;		
	}
	return (exp.j);
}

