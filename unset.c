#include "mini.h"

/*
	if pipe exist unset ignored
	if without argument ignored
	examples:
	*- unset USER PWD
*/

void	ft_unset(t_command *commands, t_parser *parser)
{
	int		i;
	t_env	*current;
	t_env	*previous;

	i = 1;
	if (parser->nb_pipes > 0 || !commands->command[1])
	{
		parser->exit_status = 0;
		//test_print_env(parser->envs);
		return ;
	}
	while (commands->command[i])
	{
		current = parser->envs;
		previous = NULL;
		while (current != NULL)
		{
			if (strcmp(current->key, commands->command[i]) == 0)
			{
				if (previous == NULL)
				{
					parser->envs = current->next;
				}
				else
				{
					previous->next = current->next;
				}
				free(current->key);
				free(current->value);
				free (current);
				break;
			}
			previous = current;
			current = current->next;
		}
		i++;
	}
	parser->exit_status = 0;
	//test_print_env(parser->envs);
}