#include "mini.h"


/// ******subshell handle -> exit from subshell

// void	free_arrs(char **str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		printf("str: %s\n", str[i]);
// 		free(str[i]);
// 		i++;
// 	}
// 	free(str);
// }

static long long	ft_atoll(const char *str)
{
	long long	n;
	int			is_negative;

	n = 0;
	is_negative = false;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		is_negative = (*str == '-');
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		n = (n * 10) + (*str - '0');
		str++;
	}
	if (is_negative)
		return (-n);
	return (n);
}

static bool	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

/*
	first check if there is a pipe (not perform an exit)-> the command is part of a pipeline.
	no args ->simple exit, args? numeric?multiple?
	examples:
	*- exit 1000
		exit (232 (1000%256))
	*- exit 100 47 -> (did not exit)
		exit
		bash: exit: too many arguments (1)
	*- exit salam / exit salam khobi
		exit
		bash: exit: salam: numeric argument required (2)
	*- exit
		exit (0)
	*- exit | echo "kimia" -> (did not exit)
		kimia (0)
	*- exit > outfile
		exit (127)
*/

void	ft_terminate(int status, t_parser *parser)
{
	//free
	//free_arrs(parser->commands->command);
	printf("status:%d\n", parser->exit_status);
	free(parser->commands->command);
	free(parser->commands);
	free(parser);
	exit(status);
}

void	ft_exit(t_command *commands, t_parser *parser)
{
	if (parser->nb_pipes > 0)
	{
		parser->exit_status = 0;
		return ;
	}
	if (commands->command[0] && !commands->command[1])
	{
		ft_putstr_fd("exit\n", 2);
		parser->exit_status = 0;
		ft_terminate(0, parser);
	}
	if (!is_num(commands->command[1]))
	{
		ft_putstr_fd("exit\nminishell: exit: ", 2);
		ft_putstr_fd(commands->command[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		parser->exit_status = 2;
		ft_terminate(2, parser);
	}
	if (commands->command[2])
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		parser->exit_status = 1;
		return ;
	}
	ft_putstr_fd("exit\n", 2);
	parser->exit_status = (ft_atoll(commands->command[1]) % 256);
	ft_terminate(parser->exit_status, parser);
}