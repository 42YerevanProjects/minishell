#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <termios.h>
# include <dirent.h>
# include <sys/wait.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>


# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SUCCESS 0
# define ERROR 1
# define EXPANSION -36
# define DIRECTORY 126
# define UNKNOWN_COMMAND 127


/* For storing information about every command */
typedef struct	s_cmd
{
	char	**args;
	int		in;
	int		out;
	char	**heredoc;
	char	**refine;
}				t_cmd;

/* For storing information about tokens and quotes */
typedef struct s_token 
{
	char	**token_array;
	char	**quote_array;
}				t_token;

/* For dealing with expansions */
typedef struct s_expansion
{
	int	expand;
	int	i;
	int	j;
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
	t_token	*tokens;
	t_env	*env;
	t_cmd	*commands;
	pid_t	*fam;
	int		cmd_count;
	int		status;
}				t_mini;


/* UTILS */
int		init(t_mini *mini, char **env);
void	increment_shell_level(t_env *env);
int		ft_matrixlen(char **matrix);
int		ft_minishell_error(char *msg);
int		token_num(char *line);
int		ft_isspace(char c);
int		ft_abs(int nb);

/* SIGNALS */
void	sig_init(void);
void	sig_default(void);
void	sig_ignore(void);

/* PARSING */
void	parse(t_mini *mini, char *line);
void	get_tokens(t_mini *mini, char *line);
int		extract_token(t_mini *mini, char *line);

#endif
