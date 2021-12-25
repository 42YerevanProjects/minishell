#include "../../includes/minishell.h"

void	get_tokens(t_mini *mini, char *line)
{
	int	i;

	i = 0;
	mini->tokens = ft_calloc(1, sizeof(t_token));
	if (!line){
		mini->tokens = NULL;
		return ;
	}
	while (line[i])
	{
		i += extract_token(mini, &line[i]);
		break ; // this is done for testing
	}
}
