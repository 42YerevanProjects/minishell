/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalaban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:46:34 by abalaban          #+#    #+#             */
/*   Updated: 2022/01/07 12:46:12 by abalaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* SIGNAL FUNCTIONS */

void	sig_init(void)
{
	signal(SIGINT, reprompt);
	signal(SIGQUIT, sigquit);
}

void	sig_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	sig_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_heredoc(void)
{
	signal(SIGINT, interrupt);
	signal(SIGQUIT, sigquit);
}
