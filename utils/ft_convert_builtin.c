/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abalaban <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:46:34 by abalaban          #+#    #+#             */
/*   Updated: 2022/01/07 12:46:12 by abalaban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_convert_builtin(char *builtin)
{
	if (!ft_strcmp(builtin, "echo"))
		return (_ECHO);
	else if (!ft_strcmp(builtin, "cd"))
		return (_CD);
	else if (!ft_strcmp(builtin, "pwd"))
		return (_PWD);
	else if (!ft_strcmp(builtin, "export"))
		return (_EXPORT);
	else if (!ft_strcmp(builtin, "unset"))
		return (_UNSET);
	else if (!ft_strcmp(builtin, "env"))
		return (_ENV);
	else if (!ft_strcmp(builtin, "exit"))
		return (_EXIT);
	return (0);
}
