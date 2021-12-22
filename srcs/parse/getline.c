#include "../../includes/minishell.h"

void getline(t_mini *mini)
{
	char *line;
	t_token *token;

	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);

}
