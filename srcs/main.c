#include "../includes/minishell.h"

int main(int argc, char **argv, char **env)
{
	t_mini	mini;
	char	*line;

	(void) argc;
	(void) argv;
	init(&mini, env);
	sig_init();
	while (1)
	{
		line = readline("\033[0;36m\033[1m minishell ▸ \033[0m");

	}
	printf("%s\n", line);
	return (0);
}

