#include "../includes/minishell.h"
t_mini g_mini;

int main(int argc, char **argv, char **env)
{
	char	*line;

	(void) argc;
	(void) argv;
	init(&g_mini, env);
	sig_init();
	while (42)
	{
		line = readline("\001\033[1;34m\002minishell ▸ \001\033[0;0m\002");
		if (!line)
		{
			ft_putstr_fd("minishell: exit 💚", STDERR);
			return (SUCCESS);
		}
		parse_and_execute(line);
		if (ft_strcmp(line, ""))
			add_history(line);
		free(line);
	}
	return (SUCCESS);
}

