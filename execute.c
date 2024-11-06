#include "mini.h"

/* start of the execution 
example: echo  "kimia" | ls |  grep  "b";
		 ----   -----    --    ----   -- 
		 tk[0]  tk[1]   tk[0]  tk[0]  tk[1]
         ------------    --    -----------
		   	cmd[0]	    cmd[1]   cmd[2]

command => tokenlist
*/

/* compare the string to builtins 
	return value: enum of type builin*/

// static int	change_fd(t_parser *parser)
// {
// 	int	fd;

// 	if (parser->outfile == NULL)
// 		fd = STDOUT_FILENO;
// 	else
// 		fd = parser->fd_outfile;
// 	return (fd);
// }

static t_builtin	get_builtin_command(const char *cmd)
{
	if (!strcmp(cmd, "echo"))
		return (ECH);
	if (!strcmp(cmd, "cd"))
		return (CD);
	if (!strcmp(cmd, "pwd"))
		return (PWD);
	if (!strcmp(cmd, "env"))
		return (ENV);
	// if (!strcmp(cmd, "export"))
	// 	return (EXPORT);
	if (!strcmp(cmd, "unset"))
		return (UNSET);
	if (!strcmp(cmd, "exit"))
		return (EXIT);
	return (UNKNOWN);
}

bool	check_builtin(t_command *commands, t_parser *parser)
{
	t_builtin	cmd;

	cmd = get_builtin_command(commands->command[0]);
	if (cmd == ECH)
		return (ft_echo(commands, parser), true);
	if (cmd == CD)
		return (ft_cd(commands, parser), true);
	if (cmd == PWD)
		return (ft_pwd(commands, parser), true);
	if (cmd == ENV)
		return (ft_env(commands, parser), true);
	// if (cmd == EXPORT)
	// 	return (ft_export(commands, parser), true);
	if (cmd == UNSET)
		return (ft_unset(commands, parser), true);
	if (cmd == EXIT)
		return (ft_exit(commands, parser), true);
	return (false);
}

int	first_pipe(t_command *temp, int *fds)
{
	if (temp->infile_fd == -1)
		return (EXIT_FAILURE);
	if (temp->infile_fd != -2)
	{
		if (dup2(temp->infile_fd, STDIN_FILENO) == -1)
		{
			return (EXIT_FAILURE);
		}
		close(temp->infile_fd);
	}
	if (temp->outfile_fd == -1)
		return(EXIT_FAILURE);
	if (temp->outfile_fd != -2)
	{
		if (dup2(temp->outfile_fd, STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	else
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	last_pipe(t_command *temp, int *fds)
{
	if (temp->outfile_fd == -1)
		return (EXIT_FAILURE);
	if (temp->outfile_fd != -2)
	{
		if (dup2(temp->outfile_fd, STDOUT_FILENO) == -1)
		{
			return (EXIT_FAILURE);
		}
		close(temp->outfile_fd);
	}
	if (temp->infile_fd == -1)
		return(EXIT_FAILURE);
	if (temp->infile_fd != -2)
	{
		if (dup2(temp->infile_fd, STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	else
	{
		if (dup2(fds[0], STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	middle_pipe(t_command *temp, int *fds)
{
	if (temp->infile_fd == -1)
		return(EXIT_FAILURE);
	if (temp->infile_fd != -2)
	{
		if (dup2(temp->infile_fd, STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	else
	{
		if (dup2(fds[0], STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	if (temp->outfile_fd == -1)
		return(EXIT_FAILURE);
	if (temp->outfile_fd != -2)
	{
		if (dup2(temp->outfile_fd, STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	else
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_dup(t_command *temp, t_exe *exec, int i, int nb_pipes)
{
	if (i == 0)
	{
		if (first_pipe(temp, exec->fd) == EXIT_FAILURE)
			return(EXIT_FAILURE);
	}
	else if (i == nb_pipes)
	{
		if (last_pipe(temp, exec->fd) == EXIT_FAILURE)
			return(EXIT_FAILURE);
	}
	else
	{
		if (middle_pipe(temp, exec->fd) == EXIT_FAILURE)
			return(EXIT_FAILURE);
	}
	close(exec->fd[0]);
	close(exec->fd[1]);
	return (EXIT_SUCCESS);
}

void	ft_child(t_parser *parser, t_command *temp, t_exe *exec)
{
	// find/have/check path
	if (ft_dup(temp, exec, exec->i, parser->nb_pipes) == EXIT_FAILURE)
	{
		close(exec->fd[0]);
		close(exec->fd[1]);
		if (exec->read != STDIN_FILENO)
			close (exec->read);
		//free
		write_stderr("failed in dup");
		exit(EXIT_FAILURE);
	}
	if (check_builtin(temp, parser) == false)
	{
		for (int j = 0; temp->command[j]; j++)
		{
			printf("command[%d]:%s\n", j, temp->command[j]);
		}
		// for (int k = 0; parser->arg_env[k]; k++)
		// {
		// 	printf("arg[%d]:%s\n", k, parser->arg_env[k]);
		// }
		//printf("path:%s\n", temp->path);
		if (temp->path != NULL)
		{
			printf("path:%s\n", temp->path);
			execve(temp->path, temp->command, parser->arg_env);
		}
		write_stderr("Command not found");
		//free
		exit(127);
	}
	//free
	exit(EXIT_SUCCESS);
}


void	ft_parent(t_command *temp, t_exe *exec)
{
	if (temp->outfile_fd != -2 && temp->outfile_fd != -1)
		close (temp->outfile_fd);
	if (temp->infile_fd != -2 && temp->infile_fd != -1)
		close (temp->infile_fd);
	close(exec->fd[1]);
	if (exec->read != STDIN_FILENO)
		close (exec->read);
	exec->read = exec->fd[0];
}

int	pipeline(t_parser *parser)
{
	t_exe		exec;
	t_command	*temp;

	exec.read = STDIN_FILENO;
	temp = parser->commands;
	exec.i = 0;
	while (temp != NULL)
	{
		if (pipe(exec.fd) == -1)
			return (write_stderr("failed in pipe"), EXIT_FAILURE);
		exec.pid = fork();
		if (exec.pid == -1)
			return (write_stderr("failed in fork"), EXIT_FAILURE);
		if (exec.pid == 0)
			ft_child(parser, temp, &exec);
		ft_parent(temp, &exec);
		exec.i++;
		temp = temp->next;
	}
	close (exec.read);
	waitpid(exec.pid, &exec.status, 0);
	if (WIFEXITED(exec.status))
		parser->exit_status = WEXITSTATUS(exec.status);
	while (waitpid(-1, &exec.status, 0) > 0)
	{
	}
	return (parser->exit_status);
}


void	write_stderr(char *errmsg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	if (errmsg)
		ft_putstr_fd(errmsg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	execute_one_cmd(t_parser *parser, t_command *commands)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		write_stderr("failed in fork");
	if (pid == 0)
	{
		if (commands->infile_fd == -1 || commands->outfile_fd == -1)
			return (EXIT_FAILURE);
		if (commands->infile_fd >= 0)
		{
			if (dup2(commands->infile_fd, STDIN_FILENO) == -1)
				return (EXIT_FAILURE);
		}
		if (commands->outfile_fd >= 0)
		{
			if (dup2(commands->outfile_fd, STDOUT_FILENO) == -1)
				return (EXIT_FAILURE);
		}
		// for (int j = 0; commands->command[j]; j++)
		// {
		// 	printf("command[%d]:%s\n", j, commands->command[j]);
		// }
		// for (int k = 0; parser->arg_env[k]; k++)
		// {
		// 	printf("arg[%d]:%s\n", k, parser->arg_env[k]);
		// }
		// printf("path:%s\n", commands->path);
		if (commands->path != NULL)
			execve(commands->path, commands->command, parser->arg_env);
		write_stderr("Command not found");
		//free everything
		exit(127);
	}
	if (commands->infile_fd != -2)
		close (commands->infile_fd);
	if (commands->outfile_fd != -2)
		close (commands->outfile_fd);
	// if there is here doc -> unlink
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		parser->exit_status = WEXITSTATUS(status);
	return (parser->exit_status);
}


/*
	-start of execution
	-check the number of pipes for execution
	-call their functions and store and retuen the exit status
*/

// char	**find_path(int fd, char **my_path, char **cmd, char **envp)
// {
// 	int		i;
// 	int		j;
// 	char	*temp;

// 	i = -1;
// 	j = -1;
// 	while (envp[++i])
// 	{
// 		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
// 		{
// 			my_path = ft_split(envp[i] + 5, ':');
// 			if (my_path == NULL)
// 				//error
// 			while (my_path[++j])
// 			{
// 				temp = ft_strjoin(my_path[j], "/");
// 				if (temp == NULL)
// 					//error
// 				free(my_path[j]);
// 				my_path[j] = temp;
// 			}
// 			break ;
// 		}
// 	}
// 	return (my_path);
// }

int	ft_execute(t_parser *parser)
{
	int	number_pipe;

	number_pipe = parser->nb_pipes;
	if (number_pipe == 0)
	{
		if (check_builtin(parser->commands, parser) == false)
		{
			// find/have/check path
			parser->exit_status = execute_one_cmd(parser, parser->commands);
			printf("status:%d\n", parser->exit_status);
			//free path?
		}
	}
	else if (number_pipe >= 1)
	{
		parser->exit_status = pipeline(parser);
	}
	return (parser->exit_status);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	//(void)env;
	//test_echo();
	//test_pwd();
	//test_exit();
	//test_env(env);
	//test_unset(env);
	//test_cd(env);
	//test_pwd();
	//test_export(env);
	//test_one(env);
	test_one_pipe(env);
	return 0;
}