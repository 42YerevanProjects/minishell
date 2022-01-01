#include "../includes/minishell.h"

/**
 * The function closes all the descriptors of all commands except 
 * STDIN and STDOUT.
 **/

static void	ft_close_descriptors(void)
{
	int	i;

	i = 0;
	while (i < g_mini.cmd_count)
	{
		if (g_mini.commands[i].in != 0)
			close(g_mini.commands[i].in);
		if (g_mini.commands[i].out != 1)
			close(g_mini.commands[i].out);
		i++;
	}
}

/**
 * Given the command executes appropriate builtin and returns the
 * execution status. It returns 0 on sucess, -1 otherwise. 
 **/

static int	ft_exec_builtin(t_cmd *cmd)
{
	int	ret;

	ret = ft_convert_builtin(cmd->args[0]);
	if (ret == _ECHO)
		g_mini.status = ft_echo(cmd);
	else if (ret == _CD)
		g_mini.status = ft_cd(cmd);
	else if (ret == _PWD)
		g_mini.status = ft_pwd(cmd);
	else if (ret == _EXPORT)
		g_mini.status = ft_export(cmd);
	else if (ret == _UNSET)
		g_mini.status = ft_unset(cmd);
	else if (ret == _ENV)
		g_mini.status = ft_env(cmd);
	else if (ret == _EXIT)
		ft_exit(cmd);
	if (ret)
		return (0);
	return (-1);
}

/**
 * The function traverseds th binary files and trys to find the 
 * path of the command. It executes the command if finds the path, 
 * else it outputs the error.
 **/

static void	ft_traverse_binaries(t_cmd *cmd)
{
	char	**paths;
	char	*temp;
	int		i;

	/* Execut as a builtin if you get -1 enter the If block */
	if (ft_exec_builtin(cmd) == -1)
	{
		/* As we might be in the binaries folder, try executing it here */	
		execve(cmd->args[0], cmd->args, ft_env_to_array(g_mini.env));
		/* If execve fauild it will return. Continue with paths */
		if (ft_getenv("PATH"))
		{
			paths = ft_split(ft_getenv("PATH"), ':');
			i = 0;
			/* Iterate over the binary folders and try to execute */
			while (paths[i])
			{
				/* Take the new path and try to execute once more */
				temp = ft_strjoin3(paths[i], "/", cmd->args[0]);
				execve(temp, cmd->args, ft_env_to_array(g_mini.env));
				free(temp);
				i++;
			}
			ft_free_matrix(paths);
			ft_minishell_error(ft_strjoin(cmd->args[0], ": command not found"));
		}
		/* If we could not get the path */
		else
			ft_minishell_error(ft_strjoin(cmd->args[0], ": No such file or directory"));
	}
}

/**
 * The function takes the command and executes it appropriatly. It deals
 * with duplicate descriptors.
 **/

void	ft_exec(t_cmd *cmd)
{
	/* If I need to create processes for command execution */
	if (!ft_convert_builtin(cmd->args[0]) || g_mini.cmd_count != 1)
	{
		/* In the process I/O need to be connected to command streams */
		if (dup2(cmd->out, STDOUT) == -1 || dup2(cmd->in, STDIN) == -1)
		{
			perror("minishell: failed dup2");
			exit(1);
		}
		/* Close the discriptors duplicated by the processes */
		ft_close_descriptors();
		cmd->out = 1;
	}
	/* If I got a command with absolut path */
	if (cmd->args[0][0] == '/')
	{
		/* Execute it. If execve does not return then everything is ok, otherwise it is error. */
		execve(cmd->args[0], cmd->args, ft_env_to_array(g_mini.env));
		/* If execve returned, then output the error */
		ft_minishell_error(ft_strjoin(cmd->args[0], ": No such file or directory"));
	}
	/* Else we need to find the path to binary */
	else
		ft_traverse_binaries(cmd);
	/* If we could not execute the command after traversal */
	if (g_mini.cmd_count != 1 || !ft_convert_builtin(cmd->args[0]))
	{
		if (ft_convert_builtin(cmd->args[0]))
			exit(g_mini.status);
		exit(UNKNOWN_COMMAND);
	}
}

