#include "../../includes/minishell.h"

void	ft_remove_from_env(char *var)
{
	t_env	*head;
	t_env	*prev;

	head = g_mini.env;
	prev = NULL;
	while (head)
	{
		if (!ft_strcmp(ft_separate_identifier(head->value), ft_separate_identifier(var)))
		{
			if (prev == NULL)
				g_mini.env = head->next;
			else
				prev->next = head->next;
			head->next = NULL;
			head = NULL;
			break ;
		}
		prev = head;
		head = head->next;
	}
}
