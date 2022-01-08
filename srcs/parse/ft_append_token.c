/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shovsepy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:34:45 by shovsepy          #+#    #+#             */
/*   Updated: 2022/01/07 12:36:09 by shovsepy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_env_var_len(char *line)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(line[i]) || line[i] == '_'))
		return (i);
	while (ft_isalnum(line[++i]) || line[i] == '_')
		;
	return (i);
}

static int	ft_treat_dollar_sign(t_refine *r, char *line)
{
	int		env_var_len;
	char	*env;

	env_var_len = ft_env_var_len(r->ptr + 1);
	if (env_var_len)
	{
		env = ft_substr(r->ptr, 1, env_var_len);
		r->val = ft_strdup(ft_getenv(env));
		free(env);
		r->prefix = ft_substr(line, 0, r->ptr - line);
		r->postfix = ft_strdup(r->ptr + env_var_len + 1);
	}
	else if (*(r->ptr + 1) == '?')
	{
		r->val = ft_itoa(g_mini.status);
		r->prefix = ft_substr(line, 0, r->ptr - line);
		r->postfix = ft_strdup(r->ptr + 2);
	}
	else
	{
		r->ptr++;
		r->ptr = ft_strchr(r->ptr, '$');
		return (1);
	}
	return (0);
}

char	*ft_refine_line(char *line)
{
	t_refine	r;

	if (!line)
		return (NULL);
	r.ptr = ft_strchr(line, '$');
	while (r.ptr && *r.ptr)
	{
		if (ft_treat_dollar_sign(&r, line))
			continue ;
		if (r.val)
			r.ptr = ft_strjoin3(r.prefix, r.val, r.postfix);
		else
			r.ptr = ft_strjoin(r.prefix, r.postfix);
		free(line);
		line = r.ptr;
		r.ptr += ft_strlen(r.prefix) + ft_strlen(r.val);
		free(r.prefix);
		free(r.postfix);
		free(r.val);
		r.ptr = ft_strchr(r.ptr, '$');
	}
	return (line);
}

void	ft_append_token(char **token, char *line, int len, int expand)
{
	char	*str;

	str = ft_substr(line, 0, len);
	if (expand)
	{
		str = ft_refine_line(str);
		if (!ft_strcmp(str, "$"))
			return ;
		else if (str[0] == '$')
			str = ft_substr(str, 1, ft_strlen(str));
		else if (str[ft_strlen(str) - 1] == '$')
			str = ft_substr(str, 0, ft_strlen(str) - 1);
	}
	*token = ft_strjoin(*token, str);
}
