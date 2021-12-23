#include "../includes/minishell.h"

int main(int argc, char **argv, char **env)
{
	char	*line;

	(void) argc;
	(void) argv;
	init(&g_mini, env);
	increment_shell_level(g_mini.env);
	while (1)
	{
		line = readline("\033[0;36m\033[1m minishell ▸ \033[0m");

	}
	printf("%s\n", line);
	return (0);
}

