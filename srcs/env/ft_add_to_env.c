#include "../../includes/minishell.h"

void	ft_add_to_env(char *var)
{
	t_env	*head;

	head = g_mini.env;
	while (head)
	{
		if (head->next == NULL)
		{
			head->next = new_node(var, NULL);
			break ;
		}
		head = head->next;
	}
}
