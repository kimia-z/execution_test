#include "mini.h"

/* This function is doing the pwd builtin
	* What should it do when pwd variable was not found?
*/
void	ft_pwd(t_command *commands, t_parser *parser)
{
	int		outfile;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	outfile = commands->outfile_fd;
	if (outfile == -2)
		outfile = STDOUT_FILENO;
	if (pwd)
	{
		ft_putendl_fd(pwd, outfile);
	}
	free (pwd);
	parser->exit_status = 0;
}