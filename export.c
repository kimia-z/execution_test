#include "mini.h"

/// export with arguments

// void	free_env_list(t_env *list)
// {
// 	t_env	*temp;

// 	while(list)
// 	{
// 		temp = list->next;
// 		free (list);
// 		list = temp;
// 	}
// }

static t_env	*create_new_env_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(1 * sizeof(t_env));
	if (node == NULL)
		return (error_msg("failed in memory allocate\n"), NULL);
	node->key = ft_strdup(key);
	if (value != NULL)
		node->value = ft_strdup(value);
	else
		node->value = ft_strdup("");
	node->next = NULL;
	return (node);
}

void	ft_add_node(t_env **env, char *key, char *value)
{
	t_env	*temp;
	t_env	*new_node;

	temp = (*env);
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	new_node = create_new_env_node(key, value);
	temp->next = new_node;
}

static bool	env_node_checker_sign(t_env **env, char *key, char *value)
{
	t_env	*temp;
	char	**new_k;

	temp = (*env);
	new_k = ft_split(key, '=');
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, new_k[0], ft_strlen(new_k[0])) == 0)
		{
			if (value != NULL)
			{
				free(temp->key);
				temp->key = ft_strcharjoin(new_k[0], '=');
				free(temp->value);
				temp->value = ft_strdup(value);
			}
			free_2arr(new_k);
			return (true);
		}
		temp = temp->next;
	}
	free_2arr(new_k);
	return (false);
}

bool	ft_node_checker(t_env **env, char *key, char *value)
{
	t_env	*temp;

	temp = (*env);
	if (ft_node_checker_sign(env, key, value) == true)
		return (true);
	while (temp != NULL)
	{
		if (ft_strncmp(temp->key, key, sizeof(key)) == 0)
		{
			if (value != NULL)
			{
				free(temp->value);
				temp->value = ft_strdup(value);
			}
			return (true);
		}
		temp = temp->next;
	}
	return (false);
}

void	key_with_value(t_parser *parser,t_env *env, char *cmd)
{
	char	*key;
	char	*value;
	int		position;
	char	*temp;

	temp = cmd;
	position = ft_strchr_pos(cmd, '=');
	value = ft_strchr(temp, '=') + 1;
	key = malloc(position + 2 * sizeof(char));
	if (key == NULL)
	{
		parser->exit_status = 1;
		return ;
	}
	ft_strlcpy(key, cmd, position + 2);
	if (ft_node_checker(env, key, value) == false)
	{
		add_node_env(env, key, value);
	}
	if (key != NULL)
		free(key);
}

static bool	is_valid(t_parser *parser, char **current_cmd, int i)
{
	if (ft_isalpha(current_cmd[i][0]) == 0)
	{
		ft_putstr_fd("export: ", STDERR_FILENO);
		ft_putstr_fd(current_cmd[i], STDERR_FILENO);
		ft_putstr_fd(" : not valid\n", STDERR_FILENO);
		parser->exit_status = 1;
		return (false);
	}
	return (true);
}

int my_lstsize(t_env *lst)
{
	int count;

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

t_env *my_lstnew(char *key, char *value)
{
	t_env *new_node;

	new_node = (t_env *)malloc(1 * sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

t_env *my_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void my_lstadd_back(t_env **lst, t_env *new)
{
	t_env *last;

	if (!lst || !new)
		return;
	last = NULL;
	if (!*lst)
	{
		*lst = new;
		return;
	}
	else
	{
		last = my_lstlast(*lst);
		last->next = new;
	}
}

t_env *ft_copy_list(t_env *env_vars)
{
	t_env *copy_list;
	t_env *new_node;
	int len;

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
// void print_t_env(t_env *my_env)
// {
// 	t_env *temp;

// 	temp = my_env;
// 	while (temp)
// 	{
// 		ft_putstr_fd("declare -x ", 1);
// 		ft_putstr_fd(temp->key, 1);
// 		if (temp->value)
// 		{
// 			ft_putstr_fd("=\"", 1);
// 			ft_putstr_fd(temp->value, 1);
// 			ft_putchar_fd('\n', 1);
// 		}
// 		temp = temp->next;
// 	}
// }

// bubble sort the env variables
t_env *ft_sort_env(t_env *env_vars)
{
	t_env *temp_list;
	t_env *copy_list;
	char *temp;
	int len_list;

	temp_list = env_vars;
	copy_list = ft_copy_list(temp_list);
	len_list = my_lstsize(copy_list);
	while (len_list > 0)
	{
		temp_list = copy_list;
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
	return (copy_list);
}

/*
 * ft_export - Handles the export of environment variables in the shell.
 * 1) either display all environment variables in the current shell (sorted env)
 *  or to add/update environment variables based on the provided
 * arguments. If arguments are provided, it validates each argument to ensure
 * it follows the correct format for environment variable assignments,
 * and then adds or updates the variables accordingly.
 */

bool ft_node_checker(t_env *env, char *cmd)
{
	t_env *temp;

	temp = env;
	while (temp)
	{
		if (ft_strncmp(temp->key, cmd, ft_strlen(temp->key)) == 0)
		{
			if (temp->value != NULL)
			{
				free(temp->value);
				temp->value = ft_strdup;
			}
		}
		temp = temp->next;
	}
}


void print_export(t_parser *parser, int outfile)
{
	t_env *sorted_env;
	t_env *temp;

	sorted_env = ft_sort_env(parser->envs);
	temp = sorted_env;
	while (temp)
	{
		ft_putstr_fd("declare -x ", outfile);
		ft_putstr_fd(temp->key, outfile);
		if (temp->value)
		{
			ft_putstr_fd("=\"", outfile);
			ft_putstr_fd(temp->value, outfile);
			ft_putchar_fd('\n', outfile);
		}
		temp = temp->next;
	}
	free_env_list(sorted_env);
}

void ft_export(t_command *commands, t_parser *parser)
{
	int outfile;
	int i;

	i = 1;
	outfile = commands->outfile_fd;
	if (outfile == -2)
	{
		outfile = STDOUT_FILENO;
	}
	if (commands->command[1] == NULL)
	{
		print_export(parser, outfile);
		parser->exit_status = 0;
		return;
	}
	while (commands->command[i])
	{
		if (is_valid(parser, commands->command, i) == true)
		{
			if (ft_strchr(commands->command[i], '=') != NULL)
			{
				//key_value
				key_with_value(parser, parser->envs, commands->command[i]);
			}
			else
			{
				if (ft_node_checker(parser->envs, commands->command[i], NULL) == false)
				{
					ft_add_node(parser->envs, commands->command[i], NULL);
				}
			}
		}
		i++;
	}
	parser->exit_status = 0;
}
