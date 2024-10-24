#include "lexer.h"


/// ******subshell handle -> exit from subshell


long long	ft_atoll(const char *str)
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

/*
	first check if there is a pipe (not perform an exit)-> the command is part of a pipeline.
	no args ->simple exit, args? numeric?multiple?
	examples:
	*- exit 1000
		exit (zsh: command not found: 232 (1000%256))
	*- exit 100 47 -> (did not exit)
		exit
		bash: exit: too many arguments (1: command not found)
	*- exit salam / exit salam khobi
		exit
		bash: exit: salam: numeric argument required (zsh: command not found: 2)
	*- exit
		exit (zsh: command not found: 0)
	*- exit | echo "kimia" -> (did not exit)
		kimia (0: command not found)
	*- exit > outfile
		exit (zsh: command not found: 127)
*/

void	ft_terminate(int status, t_lexer *lexer)
{
	lexer->status = status;
	//free
	exit(status);
}

void	ft_exit(t_lexer *lexer)
{
	int	status;

	if (lexer->pipe > 0)
	{
		return ;
	}
	if (lexer->tokens[0] && !lexer->tokens[1])
	{
		ft_putstr_fd("exit\n", 2);
		ft_terminate(0, lexer);
	}
	if (!is_num(lexer->tokens[1]))
	{
		ft_putstr_fd("exit\nminishell: exit: ", 2);
		ft_putstr_fd(lexer->tokens[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ft_terminate(2, lexer);
	}
	if (lexer->tokens[2])
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		// need a function for error to print error and change the status
		// did not exit
		// status = 1
	}
	ft_putstr_fd("exit\n", 2);
	status = (ft_atoll(lexer->tokens[1]) % 256);
	ft_terminate(status, lexer);
}