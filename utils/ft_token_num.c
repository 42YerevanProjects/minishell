#include "../includes/minishell.h"

int	ft_token_num(char *line)
{
	char	**tokens;
	int		i;
	int		len;

	i = 0;
	len = 0;
	tokens = ft_split(line, ' ');
	while (tokens[i])
	{
		if (tokens[i][0] == '|' || tokens[i][0] == '<' || tokens[i][0] == '>')
			len++;
		len++;
		i++;
	}
	ft_free_matrix(tokens);
	return (len);
}
