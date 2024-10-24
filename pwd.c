#include "lexer.h"

/* This function is doing the pwd builtin
	* What should it do when pwd variable was not found?
*/
void	ft_pwd(t_lexer *lexer)
{
	int		outfile;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	outfile = lexer.outfile;
	if (!outfile)
	{
		outfile = STDOUT_FILENO;
	}
	if (pwd)
	{
		ft_putendl_fd(pwd, outfile);
	}
	free (pwd);
}