#include "mini.h"

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

void	ft_cd(t_command *commands, t_parser *parser)
{
	t_env	*temp;
	char	*dir;

	temp = parser->envs;
	if (!commands->command[1])
	{
		temp = ft_search_list("HOME", parser->envs);
		if (!temp)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			parser->exit_status = 1;
			return ;
		}
		dir = temp->value;
	}
	else if (commands->command[2])
	{
		ft_putstr_fd("minishel: cd: too many arguments\n", 2);
		parser->exit_status = 1;
		return ;
	}
	else
	{
		dir = commands->command[1];
	}
	printf("dir:%s\n", dir);
	if (chdir(dir) != 0)
	{
		ft_putstr_fd("minishel: cd: ", 2);
		printf("%s: ", commands->command[1]);
		ft_putstr_fd("No such file or directory\n", 2);
		parser->exit_status = 1;
		return ;
	}
	parser->exit_status = 0;
	//ft_change_dir(parser, dir);
}