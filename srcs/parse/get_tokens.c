/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c	                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shovsepy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:34:45 by shovsepy          #+#    #+#             */
/*   Updated: 2022/01/07 12:36:09 by shovsepy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init_token_array(char *line)
{
	int	num;

	num = ft_token_num(line) + 1;
	g_mini.tokens->size = 0;
	g_mini.tokens->token_array = (char **)malloc(sizeof(char *) * num);
	g_mini.tokens->quote_array = (char **)malloc(sizeof(char *) * num);
}

static void	add_token_array(char *token, char *quote)
{
	int	index;

	index = g_mini.tokens->size;
	g_mini.tokens->token_array[index] = token;
	g_mini.tokens->quote_array[index] = quote;
	g_mini.tokens->size++;
}

void	get_tokens(char *line)
{
	int			i;
	char		*token;	
	char		*quote;	

	i = 0;
	g_mini.tokens = ft_calloc(1, sizeof(t_token));
	if (line)
		init_token_array(line);
	else
		return ;
	while (line[i])
	{
		i += extract_token(&line[i], &token, &quote);
		if (token != NULL && quote != NULL)
			add_token_array(token, quote);
	}
	add_token_array(NULL, NULL);
}
