#include "../../includes/minishell.h"

void	ft_remove_from_env(char *var)
{
	t_env	*head;
	t_env	*prev;

	head = g_mini.env;
	prev = NULL;
	while (head)
	{
		if (!ft_strcmp(head->value, var))
		{
			prev->next = head->next;
			head->next = NULL;
			head = NULL;
			break ;
		}
		prev = head;
		head = head->next;
	}
}
