#include "../includes/minishell.h"

int main(int argc, char **argv, char **env)
{
	t_mini mini;

	(void) argc;
	(void) argv;
	init(&mini, env);
}
