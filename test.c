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

void	test_one(char **envp)
{
	int i = 0;
	int len = 0;
	while (envp[len] != NULL)
	{
		len++;
	}
	//printf("len:%d\n", len);
	t_parser	*parser = malloc (sizeof(t_parser));
	t_command	*commands = malloc(sizeof(t_command));
	t_env	*env = initial_env(envp);
	parser->arg_env = malloc (sizeof(char *) * (len + 1));
	while (i < len)
	{
		parser->arg_env[i] = ft_strdup(envp[i]);
		//printf("parser->arg_env[%d]:%s\n", i, parser->arg_env[i]);
		i++;
	}
	parser->arg_env[len] = NULL;
	char **cmds = malloc (sizeof(char *) * 3);
	cmds[0] = "ls";
	cmds[1] = "-la";
	cmds[2] = NULL;
	commands->next = NULL;
	commands->path = "/bin/ls";
	commands->infile_fd = -2;
	commands->outfile_fd = -2;
	commands->command = cmds;
	parser->commands = commands;
	parser->exit_status = -2;
	parser->nb_pipes = 0;
	parser->envs = env;
	
	ft_execute(parser);
}

void	test_one_pipe(char **envp)
{
	int i = 0;
	int len = 0;
	while (envp[len] != NULL)
		len++;
	t_parser	*parser = malloc (sizeof(t_parser));
	t_command	*commands = malloc(sizeof(t_command));
	t_env	*env = initial_env(envp);
	parser->arg_env = malloc (sizeof(char *) * (len + 1));
	while (i < len)
	{
		parser->arg_env[i] = ft_strdup(envp[i]);
		//printf("parser->arg_env[%d]:%s\n", i, parser->arg_env[i]);
		i++;
	}
	parser->arg_env[len] = NULL;
	char **cmd1 = malloc (sizeof(char *) * 3);
	cmd1[0] = "ls";
	cmd1[1] = "-la";
	cmd1[2] = NULL;
	char **cmd2 = malloc (sizeof(char *) * 3);
	cmd2[0] = "grep";
	cmd2[1] = "mini";
	cmd2[2] = NULL;
	commands->command = cmd1;
	commands->path = "/bin/ls";
	commands->infile_fd = -2;
	commands->outfile_fd = -2;
	commands->next = malloc(sizeof(t_command));
	commands->next->command = cmd2;
	commands->next->infile_fd = -2;
	commands->next->outfile_fd = -2;
	commands->next->path = "/bin/grep";
	commands->next->next = NULL;
	parser->commands = commands;
	parser->exit_status = -2;
	parser->nb_pipes = 1;
	parser->envs = env;
	
	ft_execute(parser);
}

void	test_two_pipe(char **envp)
{
	int i = 0;
	int len = 0;
	while (envp[len] != NULL)
		len++;
	t_parser	*parser = malloc (sizeof(t_parser));
	t_command	*commands = malloc(sizeof(t_command));
	t_env	*env = initial_env(envp);
	parser->arg_env = malloc (sizeof(char *) * (len + 1));
	while (i < len)
	{
		parser->arg_env[i] = ft_strdup(envp[i]);
		//printf("parser->arg_env[%d]:%s\n", i, parser->arg_env[i]);
		i++;
	}
	parser->arg_env[len] = NULL;
	char **cmd1 = malloc (sizeof(char *) * 3);
	cmd1[0] = "ls";
	cmd1[1] = "-la";
	cmd1[2] = NULL;
	char **cmd2 = malloc (sizeof(char *) * 3);
	cmd2[0] = "grep";
	cmd2[1] = "mini";
	cmd2[2] = NULL;
	char **cmd3 = malloc (sizeof(char *) * 3);
	cmd3[0] = "wc";
	cmd3[1] = "-l";
	cmd3[2] = NULL;
	commands->command = cmd1;
	commands->path = "/bin/ls";
	commands->infile_fd = -2;
	commands->outfile_fd = -2;
	commands->next = malloc(sizeof(t_command));
	commands->next->command = cmd2;
	commands->next->infile_fd = -2;
	commands->next->outfile_fd = -2;
	commands->next->path = "/bin/grep";
	commands->next->next = malloc(sizeof(t_command));
	commands->next->next->command = cmd3;
	commands->next->next->infile_fd = -2;
	commands->next->next->outfile_fd = -2;
	commands->next->next->path = "/bin/wc";
	commands->next->next->next = NULL;
	parser->commands = commands;
	parser->exit_status = -2;
	parser->nb_pipes = 2;
	parser->envs = env;
	
	ft_execute(parser);
}