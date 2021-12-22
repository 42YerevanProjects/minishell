#include "../includes/minishell.h"

void	sig_init(void)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.status = 0;
	g_sig.pid = 0;
}

void	sig_int(void)
{
	
	if (g_sig.pid == 0)
	{
		ft_putendl_fd("\b\b  ", STDERR);
		ft_putstr_fd("\033[0;36m\033[1m🤬 minishell ▸ \033[0m", STDERR);
		g_sig.status = 1;
	}
	else
	{
		ft_putendl_fd("", STDERR);
		g_sig.status = 130;
	}
	g_sig.sigint = 1;
}

void	sig_quit(int code)
{
	char *nbr;

	nbr = ft_itoa(code);
	if (g_sig.pid != 0)
	{
		ft_putstr_fd("Quit: ", STDERR);
		ft_putendl_fd(nbr, STDERR);
		g_sig.status = 131;
		g_sig.sigquit = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", STDERR);
	ft_memdel(nbr);
}
