#include "lexer.h"

////change directory function

/*
	If no directory argument is provided, it changes to the `HOME` dir.
	If more than one argument is provided, -> error).
*/

t_env	*ft_search_list(char *key, t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key)) == 0)
		{
			return(temp);
		}
		temp = temp->next;
	}
	return (NULL);
}

void	ft_cd(t_lexer *lexer)
{
	t_env	*temp;
	char	*dir;

	//temp = lexer->env;
	if (!lexer->tokens[1])
	{
		temp = ft_search_list("HOME", lexer->env);
		if (!temp)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return ;
		}
		dir = temp->value;
	}
	else if (lexer->tokens[2])
	{
		ft_putstr_fd("minishel: cd: too many arguments\n", 2);
		return ;
	}
	else
	{
		dir = lexer->tokens[1];
	}
	ft_change_dir(lexer, dir);
}