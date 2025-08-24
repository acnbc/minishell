/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/15 09:18:40 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/24 15:07:59 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_tokens(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static void	free_args(char **args, int count)
{
	while (count > 0)
		free(args[--count]);
	free(args);
}

static char	**copy_args_loop(t_token *tokens, int count)
{
	char	**args;
	t_token	*current;
	int		i;

	args = (char **)ft_calloc((count + 1), sizeof(char *));
	if (!args)
		return (NULL);
	current = tokens;
	i = 0;
	while (current)
	{
		args[i] = ft_strdup(current->value);
		if (!args[i])
		{
			free_args(args, i);
			return (NULL);
		}
		current = current->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

char	**copy_args(t_token *tokens)
{
	int	count;

	if (!tokens)
		return (NULL);
	count = count_tokens(tokens);
	return (copy_args_loop(tokens, count));
}

int	get_args(t_process *process_list)
{
	t_process	*current;

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
