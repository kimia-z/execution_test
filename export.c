#include <lexer.h>

///export with arguments

typedef struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
}	t_env;

void	free_env_list(t_env *list)
{
	t_env	*temp;

	while(list)
	{
		temp = list->next;
		free (list);
		list = temp;
	}
}

int	my_lstsize(t_env *lst)
{
	int		count;

	count = 0;
	if (lst == NULL)
		return (count);
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

t_env	*my_lstnew(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(1 * sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

t_env	*my_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	my_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!lst || !new)
		return ;
	last = NULL;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	else
	{
		last = my_lstlast(*lst);
		last->next = new;
	}
}

t_env	*ft_copy_list(t_env *env_vars)
{
	t_env	*copy_list;
	t_env	*new_node;
	int		len;

	len = my_lstsize(env_vars);
	while (len > 0)
	{
		new_node = my_lstnew(env_vars->key, env_vars->value);
		my_lstadd_back(&copy_list, new_node);
		env_vars = env_vars->next;
		len--;
	}
	return (copy_list);
}


//bubble sort the env variables
t_env	*ft_sort_env(t_env *env_vars)
{
	t_env	*temp_list;
	t_env	*copy_list;
	char	*temp;
	int		len_list;

	temp_list = env_vars;
	copy_list = ft_copy_list(temp_list);
	temp_list = copy_list;
	len_list = my_lstsize(copy_list);
	while (len_list > 0)
	{
		while (temp_list && temp_list->next)
		{
			if (strcmp(temp_list->key, temp_list->next->key) > 0)
			{
				temp = temp_list->key;
				temp_list->key = temp_list->next->key;
				temp_list->next->key = temp;
				temp = temp_list->value;
				temp_list->value = temp_list->next->value;
				temp_list->next->value = temp;
			}
			temp_list = temp_list->next;
		}
		len_list--;
	}
	return(copy_list);
}
/**
 * ft_export - Handles the export of environment variables in the shell.
 * 1) either display all environment variables in the current shell (sorted env)
 *  or to add/update environment variables based on the provided
 * arguments. If arguments are provided, it validates each argument to ensure
 * it follows the correct format for environment variable assignments, 
 * and then adds or updates the variables accordingly.
 */

void	print_export(t_lexer *lexer, int outfile)
{
	t_env	*sorted_env;
	t_env	*temp;

	sorted_env = ft_sort_env(lexer->env);
	temp = sorted_env;
	while (temp)
	{
		ft_putstr_fd("declare -x ", outfile);
		ft_putstr_fd(temp->key, outfile);
		if (temp->value)
		{
			ft_putstr_fd("=\"", outfile);
			ft_putstr_fd(temp->value, outfile);
			ft_putchar_fd('"', outfile);
		}
		temp = temp->next;
	}
	free_env_list(sorted_env);
}

void	ft_export(t_lexer *lexer)
{
	int	outfile;
	int	i;

	i = 1;
	//outfile = lexer.outfile;
	if (!outfile)
	{
		outfile = STDOUT_FILENO;
	}
	if (lexer->tokens[1] == NULL)
	{
		print_export(lexer, outfile);
		return ;
	}
	while (lexer->tokens[i])
	{
		// parse and (add or modified) env variables
		i++;
	}
}
