#include "mini.h"

void	ft_env(t_command *commands, t_parser *parser)
{
	int		outfile;
	t_env	*temp;

	temp = parser->envs;
	outfile = commands->outfile_fd;
	if (outfile == -2)
		outfile = STDOUT_FILENO;
	if (!parser || !parser->envs)
	{
		return(ft_putstr_fd("Error: no env variables available\n", 2));
	}
	if (commands->command[1])
	{
		printf("env: '%s': No such file or directory\n", commands->command[1]);
		return ;
	}
	while (temp)
	{
		if (temp->value)
		{
			ft_putstr_fd(temp->key, outfile);
			ft_putchar_fd('=', outfile);
			ft_putendl_fd(temp->value, outfile);
		}
		temp = temp->next;
	}
	parser->exit_status = 0;
}
