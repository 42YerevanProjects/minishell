/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shovsepy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:34:45 by shovsepy          #+#    #+#             */
/*   Updated: 2022/01/07 12:36:09 by shovsepy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*new_node(char *value, t_env *next)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->value = value;
	new->next = next;
	return (new);
}

static int	init_env(t_env **mini_env, char **env)
{
	t_env	*environ;
	int		i;

	i = 0;
	environ = new_node(ft_strdup(env[i++]), NULL);
	if (!environ)
		return (-1);
	*mini_env = environ;
	while (env[i] && mini_env)
	{
		environ->next = new_node(ft_strdup(env[i++]), NULL);
		environ = environ->next;
	}
	return (0);
}

int	init(t_mini *mini, char **env)
{
	mini->status = 0;
	mini->cmd_count = 0;
	if (init_env(&mini->env, env) == -1)
		return (-1);
	increment_shell_level(mini->env);
	return (0);
}
