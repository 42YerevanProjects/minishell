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

typedef struct s_token 
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_expansion
{
	char	*new_arg;
	int		i;
	int		j;
}				t_expansion;

typedef struct s_sig
{
	pid_t	pid;
	int		sigint;
	int		sigquit;
	int		status;
}				t_sig;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;


typedef struct s_mini
{
	t_token	*start;
	t_env	*env;
	t_env	*secret_env;
	int		in;
	int		out;
	int		fdin;
	int		fdout;
	int		pipin;
	int		pipout;
	int		pid;
	int		charge;
	int		parent;
	int		last;
	int		ret;
	int		exit;
	int		no_exec;
}				t_mini;

extern t_sig g_sig;

// utils
int		init(t_mini *mini, char **env);
void	reset_fds(t_mini *mini);

// env
void	increment_shell_level(t_env *env);

//signal
void	sig_init();
void	sig_int();
void	sig_quit(int code);

// parsing

#endif
