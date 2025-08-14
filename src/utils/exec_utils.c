#include "../../includes/minishell.h"

char	**copy_args(t_token *tokens)
{
	char	**args;
	t_token	*current;
	int		i;

	if (!tokens)
		return (NULL);
	current = tokens;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	args = (char **)safe_malloc((i + 1) * sizeof(char *));
	current = tokens;
	i = 0;
	while (current)
	{
		args[i] = ft_strdup(current->value);
		if (!args[i])
		{
			// libera os args já alocados até aqui
			while (i > 0)
				free(args[--i]);
			free(args);
			return (NULL);
		}
		i++;
		current = current->next;
	}
	args[i] = NULL;
	return (args);
}

int	get_args(t_process *process_list)
{
	t_process *current;

	current = process_list;
	while (current)
	{
		current->args = copy_args(current->tokens);
		if (!current->args)
			return (0);
		current = current->next;
	}
	return (1);
}