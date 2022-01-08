/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shovsepy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 12:34:45 by shovsepy          #+#    #+#             */
/*   Updated: 2022/01/07 12:36:09 by shovsepy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
typedef struct s_cmd
{
	char	**args;
	int		in;
	int		out;
	int		s;
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

/* A struct that helps to store and work heredoc information */
typedef struct s_heredoc
{
	int		j;
	int		heredocs;
	int		h_pid;
	int		h_status;
	int		*w_ends;
	int		refined;
	char	*heredoc;
}				t_heredoc;

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
int		ft_heredoc_size(char **token_array);
void	ft_free_commands(t_cmd *cmds);
void	ft_free_matrix(char **matrix);
int		ft_convert_builtin(char *builtin);
int		init(t_mini *mini, char **env);
char	**ft_array_copy(char **args);
int		ft_minishell_error(char *msg);
int		ft_matrixlen(char **matrix);
t_cmd	*ft_find_command(pid_t pid);
int		ft_token_num(char *line);
int		ft_args_size(int index);
void	ft_free_tokens(void);
int		ft_isnum(char *num);
int		ft_isspace(char c);
void	ft_free_fam(void);
int		ft_abs(int nb);

/* ENV UTILS */
t_env	*new_node(char *value, t_env *next);
void	increment_shell_level(t_env *env);
int		ft_is_valid_identifier(char *var);
int		ft_is_valid_declaration(char *decl);
char	*ft_separate_identifier(char *var);
char	**ft_env_to_array(t_env *enc);
void	ft_remove_from_env(char *var);
int		ft_env_contains(char *var);
void	ft_add_to_env(char *var);
char	*ft_getenv(char *var);
void	ft_print_env(int fd);

/* SIGNALS */
void	sig_init(void);
void	sig_default(void);
void	sig_ignore(void);
void	sig_heredoc(void);

void	supress_output(void);
void	reprompt(int sig);
void	sigquit(int sig);
void	interrupt(int sig);

/* PARSING */
void	parse_and_execute(char *line);
void	get_tokens(char *line);
int		extract_token(char *line, char **token, char **quote);
int		extract_argument(t_cmd *cmd, int *index);
void	ft_append_token(char **token, char *line, int len, int expand);
void	parse_commands(void);
int		check_pipe(char **args, int *index);
char	*ft_refine_line(char *line);

/* HEREDOC */
int		launch_heredoc(void);
void	process_heredoc(t_heredoc *h_info);
void	ft_alloc_heredoc(t_cmd *cmd);
void	ft_alloc_refine(t_cmd *cmd);

/* BUILTINS  */
int		ft_echo(t_cmd *cmd);
int		ft_cd(t_cmd *cmd);
int		ft_pwd(t_cmd *cmd);
int		ft_export(t_cmd *cmd);
int		ft_unset(t_cmd *cmd);
int		ft_env(t_cmd *cmd);
void	ft_exit(t_cmd *cmd);

/* EXECUTING */
void	ft_exec(t_cmd *cmd);

#endif
