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
	if (!strcmp(cmd, "export"))
		return (EXPORT);
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
	// if (cmd == CD)
	// 	return (ft_cd(commands, parser), true);
	// if (cmd == PWD)
	// 	return (ft_pwd(commands, parser), true);
	// if (cmd == ENV)
	// 	return (ft_env(commands, parser), true);
	// if (cmd == EXPORT)
	// 	return (ft_export(commands, parser), true);
	// if (cmd == UNSET)
	// 	return (ft_unset(commands, parser), true);
	// if (cmd == EXIT)
	// 	return (ft_exit(commands, parser), true);
	return (false);
}
/*
int	first_pipe(t_parser *parser, int *fds)
{
	if (parser->infile_fd == -1)
		return (EXIT_FAILURE);
	if (parser->infile_fd != -2)
	{
		if (dup2(parser->infile_fd, STDIN_FILENO) == -1)
		{
			return (EXIT_FAILURE);
		}
		close(parser->infile_fd);
	}
	if (parser->outfile_fd == -1)
		return(EXIT_FAILURE);
	if (parser->outfile_fd != -2)
	{
		if (dup2(parser->outfile_fd, STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	else
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	last_pipe(t_parser *parser, int *fds)
{
	if (parser->outfile_fd == -1)
		return (EXIT_FAILURE);
	if (parser->outfile_fd != -2)
	{
		if (dup2(parser->outfile_fd, STDOUT_FILENO) == -1)
		{
			return (EXIT_FAILURE);
		}
		close(parser->outfile_fd);
	}
	if (parser->infile_fd == -1)
		return(EXIT_FAILURE);
	if (parser->infile_fd != -2)
	{
		if (dup2(parser->infile_fd, STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	else
	{
		if (dup2(fds[0], STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	middle_pipe(t_parser *parser, int *fds)
{
	if (parser->infile_fd == -1)
		return(EXIT_FAILURE);
	if (parser->infile_fd != -2)
	{
		if (dup2(parser->infile_fd, STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	else
	{
		if (dup2(fds[0], STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	if (parser->outfile_fd == -1)
		return(EXIT_FAILURE);
	if (parser->outfile_fd != -2)
	{
		if (dup2(parser->outfile_fd, STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	else
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_dup(t_parser *parser, int *fds, int read, int i)
{
	if (i == 0)
	{
		if (first_pipe(parser, fds) == EXIT_FAILURE)
			return(EXIT_FAILURE);
	}
	else if (i == parser->nb_pipes)
	{
		if (last_pipe(parser, fds) == EXIT_FAILURE)
			return(EXIT_FAILURE);
	}
	else
	{
		if (middle_pipe(parser, fds) == EXIT_FAILURE)
			return(EXIT_FAILURE);
	}
	close(fds[0]);
	close(fds[1]);
	return (EXIT_SUCCESS);
}

void	ft_child(t_parser *parser, int *fds, int read, int i)
{
	// find/have/check path
	if (dup_manager(parser, fds, read, i) == EXIT_FAILURE)
	{
		close(fds[0]);
		close(fds[1]);
		if (read != STDIN_FILENO)
			close (read);
		//free
		write_stderr("failed in dup");
		exit(EXIT_FAILURE);
	}
	if (check_builtin(parser->commands) == false)
	{
		if (parser->commands->path != NULL)
		{
			execve(parser->commands->path, parser->commands, parser->envp);
			write_stderr("Command not found");
			//free
			exit(127);
		}
	}
	//free
	exit(EXIT_SUCCESS);
}


void	ft_parent(t_parser *parser, int read, int *fds)
{
	if (parser->outfile_fd != -2 && parser->outfile_fd != -1)
		close (parser->outfile_fd);
	if (parser->infile_fd != -2 && parser->infile_fd != -1)
		close (parser->infile_fd);
	close(fds[1]);
	if (read != STDIN_FILENO)
		close (read);
	//read stored in data structure?
	read = fds[0];
}

int	pipeline(t_parser *parser)
{
	int			read;
	int			fds[2];
	int			pid;
	t_command	*temp;
	int			i;
	int			status;

	read = STDIN_FILENO;
	temp = parser->commands;
	i = 0;
	while (temp != NULL)
	{
		if (pipe(fds) == -1)
			return (write_stderr("failed in pipe"), EXIT_FAILURE);
		pid = fork();
		if (pid == -1)
			return (write_stderr("failed in fork"), EXIT_FAILURE);
		if (pid == 0)
			ft_child(parser, fds, read, i);
		ft_parent(parser, read, fds);
		i++;
		temp = temp->next;
	}
	close (read);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		parser->exit_status = WEXITSTATUS(status);
	while (waitpid(-1, &status, 0) > 0)
	{
	}
	return (parser->exit_status);
}

int	execute_one_cmd(t_parser *parser)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		write_stderr("failed in fork");
	if (pid == 0)
	{
		if (parser->infile_fd == -1 || parser->outfile_fd == -1)
			return (EXIT_FAILURE);
		if (parser->infile_fd >= 0)
		{
			if (dup2(parser->infile_fd, STDIN_FILENO) == -1)
				return (EXIT_FAILURE);
		}
		if (parser->outfile >= 0)
		{
			if (dup2(parser->outfile_fd, STDOUT_FILENO) == -1)
				return (EXIT_FAILURE);
		}
		if (parser->commands->path != NULL)
			execve(parser->commands->path, parser->commands->command, parser->envp);
		write_stderr("Command not found");
		//free everything
		exit(127);
	}
	//if parser->infile true
	close (parser->infile_fd);
	//if parser->outfile true
	close (parser->outfile);
	// if there is here doc -> unlink
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		parser->exit_status = WEXITSTATUS(status);
	return (parser->exit_status);
}
*/

/*
	-start of execution
	-check the number of pipes for execution
	-call their functions and store and retuen the exit status
*/

int	ft_execute(t_parser *parser)
{
	int	number_pipe;

	number_pipe = parser->nb_pipes;
	if (number_pipe == 0)
	{
		if (check_builtin(parser->commands, parser) == false)
		{
			printf("dakhel\n");
			// find/have/check path
			//parser->exit_status = execute_one_cmd(parser);
			//free path?
		}
	}
	// else if (number_pipe >= 1)
	// {
	// 	parser->exit_status = pipline(parser);
	// }
	return (parser->exit_status);
}

int main(void)
{
	//cmd1: echo "kimia"
	t_parser	parser;
	printf("hiii\n");
	parser.commands->command[0] = "echo";
	parser.commands->command[1] = "-n";
	parser.commands->command[2] = "kimia";
	parser.commands->command[3] = NULL;
	parser.commands->next = NULL;
	parser.commands->path = NULL;
	parser.commands->infile_fd = -2;
	parser.commands->outfile_fd = -2;
	parser.exit_status = -2;
	parser.nb_pipes = 0;
	
	ft_execute(&parser);
	return 0;
}