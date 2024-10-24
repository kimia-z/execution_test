#include "mini.h"

/* This function will check if the ECHO is called
	with -n options 
	example: echo -n hi
			 echo -nnnnnn hi
			 echo -n -n -n hi
*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*s1p;
	const unsigned char	*s2p;

	s1p = (const unsigned char *)s1;
	s2p = (const unsigned char *)s2;
	if (s1p == 0 && s2p == 0)
		return (0);
	while (n > 0 && *s1p && *s2p && (*s1p == *s2p))
	{
		s1p++;
		s2p++;
		n--;
	}
	if (n == 0 || (*s1p == '\0' && *s2p == '\0'))
		return (0);
	else
		return (*s1p - *s2p);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;
	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

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
		write(outfile, commands->command[position], ft_strlen(commands->command[position]));
		if (commands->command[++position])
		{
			write(outfile, " ", 1);
		}
	}
	if (is_newline)
	{
		write(outfile, "\n", 1);
	}
	parser->exit_status = 0;
}
