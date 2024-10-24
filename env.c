#include "lexer.h"

void	ft_env(t_lexer *lexer)
{
	int		outfile;
	t_env	*temp;

	temp = lexer->env;
	//outfile = lexer->outfile;
	if (!outfile)
		outfile = STDOUT_FILENO;
	if (!lexer || !lexer->env)
	{
		return(ft_putstr_fd("Error: no env variables available\n", 2));
	}
	if (lexer->tokens[1] && lexer->tokens[1] == TOKEN_WORD)
	{
		return (printf("env: '%s': No such file or directory\n", lexer->tokens[1]));
	}
	while (temp)
	{
		if (temp->value)
		{
			ft_putstr_fd(temp->key, outfile);
			ft_putchar_fd('=', outfile);
			ft_putstr_fd(temp->value, outfile);
		}
		temp = temp->next;
	}
}