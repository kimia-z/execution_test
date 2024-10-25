#include "mini.h"

/* This function will check if the ECHO is called
	with -n options 
	example: echo -n hi
			 echo -nnnnnn hi
			 echo -n -n -n hi
*/


static bool	check_newline(t_command *commands, int *position)
{
	bool	newline;
	int		count;
	char	*temp;
	int		i;

	newline = true;
	count = 1;
	while (commands->command[count] && commands->command[count][0] == '-')
	{
		i = 1;
		temp = commands->command[count];
		count++;
		if (strcmp(temp, "-n") == 0)
			newline = false;
		else if (ft_strncmp(temp, "-n", 2) == 0)
		{
			while (temp[i] && temp[i] == 'n')
				i++;
			if (temp[i - 1] == 'n' && !temp[i])
				newline = false;
		}
		else
		{
			count--;
			break;
		}
	}
	(*position) = count;
	return (newline);
}

void	ft_echo(t_command *commands, t_parser *parser)
{
	int		outfile;
	bool	is_newline;
	int		position;

	if (commands->outfile_fd == -2)
		outfile = STDOUT_FILENO;
	else
		outfile = commands->outfile_fd;
	position = 1;
	is_newline = check_newline(commands, &position);
	while (commands->command[position])
	{
		ft_putstr_fd(commands->command[position], outfile);
		if (commands->command[++position])
		{
			ft_putchar_fd(' ', outfile);
		}
	}
	if (is_newline)
	{
		ft_putchar_fd('\n', outfile);
	}
	parser->exit_status = 0;
}
