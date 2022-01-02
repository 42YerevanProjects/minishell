#include "../../includes/minishell.h"

static char	*get_name(char *var)
{
	char	*name;
	int		i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	name = (char *)malloc(sizeof(char) * i + 2);
	i = 0;
	while (var[i] && var[i] != '=')
	{
		name[i] = var[i];
		i++;
	}
	name[i] = '=';
	name[i + 1] = '\0';
	return (name);
}

void	ft_remove_from_env(char *var)
{
	t_env	*head;
	t_env	*prev;

	head = g_mini.env;
	prev = NULL;
	while (head)
	{
		if (!ft_strcmp(get_name(head->value), get_name(var)))
		{
			if (prev != NULL)
				prev->next = head->next;
			head->next = NULL;
			head = NULL;
			break ;
		}
		prev = head;
		head = head->next;
	}
}
