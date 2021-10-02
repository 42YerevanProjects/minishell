#include "../includes/minishell.h"

static t_env *new_node(char *value, t_env *next)
{
	t_env *new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->value = value;
	new->next = next;

	return new;
}

static int init_env(t_env *mini_env, char **env)
{
	t_env	*environ;
	int		i;

	i = 0;
	environ = new_node(ft_strdup(env[i++]), NULL);
	if (!environ)
		return -1;
	mini_env = environ;
	while (env[i] && mini_env)
	{
		environ->next = new_node(ft_strdup(env[i++]), NULL);
		environ = environ->next;
	}
	
	return 0;	
}

int	init(t_mini *mini, char **env)
{
	mini->ret = 0;
	mini->exit = 0;
	mini->no_exec = 0;
	mini->in = dup(STDIN);
	mini->out = dup(STDOUT);
	reset_fds(mini);
	if (init_env(mini->env, env) == -1)
		return (-1);
	if (init_env(mini->secret_env, env) == -1)
		return -1;
	return 0;
}
