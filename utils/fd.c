#include "../includes/minishell.h"

void	reset_fds(t_mini *mini)
{
	mini->pid = -1;
	mini->fdin = -1;
	mini->fdout = -1;
	mini->pipin = -1;
	mini->pipout = -1;
}
