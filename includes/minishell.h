#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <dirent.h>
# include <sys/wait.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define END 7

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SUCCESS 0
# define ERROR 1
# define EXPANSION -36
# define DIRECTORY 126
# define UNKNOWN_COMMAND 127

# define NOSKIP 0
# define SKIP 1

/* For storing information about every command */
typedef struct	s_cmd
{
	char	**args;
	int		in;
	int		out;
	char	**heredoc;
	char	**refine;
}				t_cmd;

/* For storing information about every token as a doubly linked node */
typedef struct s_token 
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

/* For dealing with expansions */
typedef struct s_expansion
{
	char	*new_arg;
	int		i;
	int		j;
}				t_expansion;

/* For storing the environment variables line by line as a node */
typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;

/* For refining the line by storing appropriate values from env */
typedef struct s_refine
{
	char		*ptr;
	char		*prefix;
	char		*postfix;
	char		*val;
}				t_refine;

/* TODO: Woking with heredocs */

typedef struct s_mini
{
	t_token	*start;
	t_env	*env;
	t_cmd	*commands;
	pid_t	*fam;
	int		cmd_count;
	int		status;
}				t_mini;

extern t_mini g_mini;

// utils
int		init(t_mini *mini, char **env);
void	reset_fds(t_mini *mini);

// env
void	increment_shell_level(t_env *env);

//signal

// parsing

#endif
