#include "../includes/minishell.h"
t_mini g_mini;

int main(int argc, char **argv, char **env)
{
	char	*line;

	(void) argc;
	(void) argv;
	init(&g_mini, env);
	sig_init();
	while (1)
	{
		line = readline("\033[0;36m\033[1mminishell ▸ \033[0m");
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

