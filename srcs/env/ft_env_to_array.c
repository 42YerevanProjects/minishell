#include "../../includes/minishell.h"

char	**ft_env_to_array(t_env *env)
{
	t_env	*head;
	char	**array;
	int		i;

	head = env;
	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	array = (char **)malloc(sizeof(char *) * i + 1);
	head = env;
	i = 0;
	while (head)
	{
		array[i++] = head->value;
		head = head->next;
	}
	array[i] = NULL;
	return (array);
}
