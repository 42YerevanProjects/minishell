#include "../../includes/minishell.h"

/**
 * The function counts and returns the length of the environment 
 * variable name. It the variable doesn't start with underscore or a
 * character then zero is returned.
 **/

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

/**
 * The function takes the referrenc of the refine struct and the line. It
 * findesthe environment variable value needed for expansion and stores it
 * in the struct r. It also stores the prefixe and postfix of the line with
 * respect to the expanded part. The function returns 0 on success and 1 if
 * no env variable found.
 **/

static int	ft_treat_dollar_sign(t_refine *r, char *line)
{
	int		env_var_len;					// stores the length of the env variable
	char	*env;							// stores the name of the env variable

	env_var_len = ft_env_var_len(r->ptr + 1);
	/* If the variable name is valid */
	if (env_var_len)
	{
		env = ft_substr(r->ptr, 1, env_var_len);		// extracts the variable name
		r->val = ft_strdup(ft_getenv(env));			// gets the env variable value
		free(env);									
		r->prefix = ft_substr(line, 0, r->ptr - line);		// stores everything before the expanded part
		r->postfix = ft_strdup(r->ptr + env_var_len + 1);	// stores everything after the expanded part
	}
	/* If the expansion is "$?" */
	else if (*(r->ptr + 1) == '?')
	{
		r->val = ft_itoa(g_mini.status);			// The value of expansion is the programm status
		r->prefix = ft_substr(line, 0, r->ptr - line);		// stores everything before expanded part 
		r->postfix = ft_strdup(r->ptr + 2);			// stores everything after the expanded part
	}
	/* Else if the variable is not valid */
	else
	{
		r->ptr++;
		/* Added this line to prevent segfault */
		r->ptr = ft_strchr(r->ptr, '$');						// find the next occurance of '$'
		return (1);
	}
	return (0);
}

/**
 * The refines the argument by perfroming expansions on it. Expansiosn
 * treat with insertion of the environment variable values in appropriate
 * positions. The function returns the refined line.
 **/

static char	*ft_refine_line(char *line)
{
	int			cont;							// stores status of line after treating '$'
	t_refine	r;								// refine struct to help deal with the process

	if (!line)
		return (NULL);
	r.ptr = ft_strchr(line, '$');				// get the first refference of '$'
	/* Traverse over the line and expand */
	while (r.ptr && *r.ptr)
	{
		/* Getting segfault here */
		cont = ft_treat_dollar_sign(&r, line);
		if (cont)
			continue ; 
		/* If environment variable value is found insert it in line */
		if (r.val)
			r.ptr = ft_strjoin3(r.prefix, r.val, r.postfix);
		/* Else exclude that part from line */
		else
			r.ptr = ft_strjoin(r.prefix, r.postfix);
		free(line);							
		line = r.ptr;								// Update line with the expaned one
		r.ptr += ft_strlen(r.prefix) + ft_strlen(r.val);			// Update the pointer 
		free(r.prefix);
		free(r.postfix);
		free(r.val);
		r.ptr = ft_strchr(r.ptr, '$');						// find the next occurance of '$'
	}
	return (line);
}

/**
 * The function takes the refference of the token and adds len characters
 * starting from line pointer. If expansion is needed it is performed on
 * the string before being added to the token.
 **/

void	ft_append_token(char **token, char *line, int len, int expand)
{
	char	*str;

	str = ft_substr(line, 0, len);
	if (expand)
		str = ft_refine_line(str);
	*token = ft_strjoin(*token, str);
}
