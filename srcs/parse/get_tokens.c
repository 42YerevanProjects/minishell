#include "../../includes/minishell.h"

void	get_tokens(char *line)
{
	int			i;
	int			num;
	char		*token;
	char		*quote;

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
	while (line[i])
	{
		i += extract_token(&line[i], &token, &quote);
		break ; // this is done for testing
	}
}
