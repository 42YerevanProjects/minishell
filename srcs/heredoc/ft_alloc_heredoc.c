/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc_heredoc.c	                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shovsepy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:34:45 by shovsepy          #+#    #+#             */
/*   Updated: 2022/01/07 12:36:09 by shovsepy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_alloc_heredoc(t_cmd *cmd)
{
	int	h_size;

	h_size = ft_heredoc_size(g_mini.tokens->token_array) + 1;
	cmd->heredoc = ft_calloc(h_size, sizeof(char *));
}

void	ft_alloc_refine(t_cmd *cmd)
{
	int	h_size;

	h_size = ft_heredoc_size(g_mini.tokens->token_array) + 1;
	cmd->refine = ft_calloc(h_size, sizeof(char *));
}
