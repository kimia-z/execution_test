#include "mini.h"

void	test_echo(void)
{
	//cmd1: echo "kimia"
	//cmd2: echo -n kimia
	//cmd3: echo -nnn kimia
	//cmd4: echo -n -n kimia

	t_parser	*parser = malloc (sizeof(t_parser));
	t_command	*commands = malloc(sizeof(t_command));
	//1:
	char **cmds = malloc (sizeof(char *) * 3);
	cmds[0] = "echo";
	cmds[1] = "kimia";
	cmds[2] = NULL;
	//4:
	// char **cmds = malloc (sizeof(char *) * 5);
	// cmds[0] = "echo";
	// cmds[1] = "-n";
	// cmds[2] = "-n";
	// cmds[3] = "kimia";
	// cmds[4] = NULL;
	commands->next = NULL;
	commands->path = NULL;
	commands->infile_fd = -2;
	commands->outfile_fd = -2;
	commands->command = cmds;
	parser->commands = commands;
	parser->exit_status = -2;
	parser->nb_pipes = 0;
	
	ft_execute(parser);
}

void	test_pwd(void)
{
	//cmd: pwd

	t_parser	*parser = malloc (sizeof(t_parser));
	t_command	*commands = malloc(sizeof(t_command));
	char **cmds = malloc (sizeof(char *) * 3);
	cmds[0] = "pwd";
	cmds[1] = "kososher";
	cmds[2] = NULL;
	commands->next = NULL;
	commands->path = NULL;
	commands->infile_fd = -2;
	commands->outfile_fd = -2;
	commands->command = cmds;
	parser->commands = commands;
	parser->exit_status = -2;
	parser->nb_pipes = 0;
	
	ft_execute(parser);
}

void	test_exit(void)
{
	//cmd1 : exit
	//cmd2 : exit 255
	//cmd3 : exit jkdhjhd
	//cmd4 : exit 39 38

	t_parser	*parser = malloc (sizeof(t_parser));
	t_command	*commands = malloc(sizeof(t_command));

	//1:
	char **cmds = malloc (sizeof(char *) * 2);
	cmds[0] = "exit";
	cmds[1] = NULL;
	//2:
	// char **cmds = malloc (sizeof(char *) * 3);
	// cmds[0] = "exit";
	// cmds[1] = "255";
	// cmds[2] = NULL;
	//3:
	// char **cmds = malloc (sizeof(char *) * 3);
	// cmds[0] = "exit";
	// cmds[1] = "kososher";
	// cmds[2] = NULL;
	//4:
	// char **cmds = malloc (sizeof(char *) * 4);
	// cmds[0] = "exit";
	// cmds[1] = "39";
	// cmds[2] = "38";
	// cmds[3] = NULL;

	commands->next = NULL;
	commands->path = NULL;
	commands->infile_fd = -2;
	commands->outfile_fd = -2;
	commands->command = cmds;
	parser->commands = commands;
	parser->exit_status = -2;
	parser->nb_pipes = 0;
	
	ft_execute(parser);
}

void	test_env(char **envp)
{
	//cmd1 : env
	//cmd2 : env isjh

	t_parser	*parser = malloc (sizeof(t_parser));
	t_command	*commands = malloc(sizeof(t_command));
	t_env	*env = initial_env(envp);
	char **cmds = malloc (sizeof(char *) * 2);
	cmds[0] = "env";
	cmds[1] = NULL;
	commands->next = NULL;
	commands->path = NULL;
	commands->infile_fd = -2;
	commands->outfile_fd = -2;
	commands->command = cmds;
	parser->commands = commands;
	parser->exit_status = -2;
	parser->nb_pipes = 0;
	parser->envs = env;
	
	ft_execute(parser);
}

void	test_unset(char **envp)
{
	//cmd1 : unset USER
	//cmd2 : unset USER PATH
	//cmd3 : unset
	//cmd4 : unset skfkgfk

	t_parser	*parser = malloc (sizeof(t_parser));
	t_command	*commands = malloc(sizeof(t_command));
	t_env	*env = initial_env(envp);
	char **cmds = malloc (sizeof(char *) * 4);
	cmds[0] = "unset";
	cmds[1] = "PWD";
	cmds[2] = "USER";
	cmds[3] = NULL;
	commands->next = NULL;
	commands->path = NULL;
	commands->infile_fd = -2;
	commands->outfile_fd = -2;
	commands->command = cmds;
	parser->commands = commands;
	parser->exit_status = -2;
	parser->nb_pipes = 0;
	parser->envs = env;
	
	ft_execute(parser);
}

void	test_print_env(t_env *envp)
{
	//cmd1 : env
	//cmd2 : env isjh

	t_parser	*parser = malloc (sizeof(t_parser));
	t_command	*commands = malloc(sizeof(t_command));
	t_env	*env = envp;
	char **cmds = malloc (sizeof(char *) * 2);
	cmds[0] = "env";
	cmds[1] = NULL;
	commands->next = NULL;
	commands->path = NULL;
	commands->infile_fd = -2;
	commands->outfile_fd = -2;
	commands->command = cmds;
	parser->commands = commands;
	parser->exit_status = -2;
	parser->nb_pipes = 0;
	parser->envs = env;
	
	ft_execute(parser);
	free_env_list(parser->envs);
	free(parser);
	free(commands);
	free(cmds);
}

void	test_cd(char **envp)
{
	//cmd1 : cd
	//cmd2 : cd path

	t_parser	*parser = malloc (sizeof(t_parser));
	t_command	*commands = malloc(sizeof(t_command));
	t_env	*env = initial_env(envp);
	// char	**cmds = malloc (sizeof(char *) * 3);
	// cmds[0] = "cd";
	// cmds[1] = "..";
	// cmds[2] = NULL;
	char	**cmds = malloc (sizeof(char *) * 3);
	cmds[0] = "cd";
	cmds[1] = "/Users/kimiaziari/codam";
	cmds[2] = NULL;
	commands->next = NULL;
	commands->path = NULL;
	commands->infile_fd = -2;
	commands->outfile_fd = -2;
	commands->command = cmds;
	parser->commands = commands;
	parser->exit_status = -2;
	parser->nb_pipes = 0;
	parser->envs = env;
	
	ft_execute(parser);
}

void	test_export(char **envp)
{
	//cmd1 : export
	//cmd2 : export USER=kimia
	//cmd3 : export VAR=new_var

	t_parser	*parser = malloc (sizeof(t_parser));
	t_command	*commands = malloc(sizeof(t_command));
	t_env	*env = initial_env(envp);
	// char **cmds = malloc (sizeof(char *) * 2);
	// cmds[0] = "export";
	// cmds[1] = NULL;
	char **cmds = malloc (sizeof(char *) * 3);
	cmds[0] = "export";
	cmds[1] = "USER=kimia";
	cmds[2] = NULL;
	commands->next = NULL;
	commands->path = NULL;
	commands->infile_fd = -2;
	commands->outfile_fd = -2;
	commands->command = cmds;
	parser->commands = commands;
	parser->exit_status = -2;
	parser->nb_pipes = 0;
	parser->envs = env;
	
	ft_execute(parser);
}