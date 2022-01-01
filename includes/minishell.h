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

# define _ECHO 1
# define _CD 2
# define _PWD 3
# define _EXPORT 4
# define _UNSET 5
# define _ENV 6
# define _EXIT 7

# define SUCCESS 0
# define ERROR 1
# define SYNTAX_ERROR 258
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
	int		size;
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

extern t_mini	g_mini;

/* UTILS */
int		ft_count_commands(char **token_array);
void	ft_free_commands(t_cmd *commands);
void	ft_free_tokens(t_token *tokens);
void	ft_free_matrix(char **matrix);
int     ft_convert_builtin(char *builtin)
int		init(t_mini *mini, char **env);
int		ft_minishell_error(char *msg);
int		ft_matrixlen(char **matrix);
int		ft_token_num(char *line);
int		ft_args_size(int index);
int		ft_isnum(char *num);
int		ft_isspace(char c);
int		ft_abs(int nb);

/* ENV UTILS */
t_env	*new_node(char *value, t_env *next);
void	increment_shell_level(t_env *env);
int		ft_is_valid_identifier(char *var);
int		ft_is_valid_declaration(char *decl);
char	*ft_separate_identifier(char *var);
void	ft_remove_from_env(char *var);
int		ft_env_contains(char *var);
void	ft_add_to_env(char *var);
char	*ft_getenv(char *var);
void	ft_print_env(int fd);

/* SIGNALS */
void	sig_init(void);
void	sig_default(void);
void	sig_ignore(void);

/* PARSING */
void	parse_and_execute(char *line);
void	get_tokens(char *line);
int		extract_token(char *line, char **token, char **quote);
int		extract_argument(t_cmd *cmd, int *index);
void	ft_append_token(char **token, char *line, int len, int expand);
void	parse_commands(void);
int		check_pipe(char **args, int *index);

/* BUILTINS  */
int		ft_echo(t_cmd *cmd);
int		ft_cd(t_cmd *cmd);
int		ft_pwd(t_cmd *cmd);
int		ft_export(t_cmd *cmd);
int		ft_unset(t_cmd *cmd);
int		ft_env(t_cmd *cmd);
void	ft_exit(t_cmd *cmd);

#endif
