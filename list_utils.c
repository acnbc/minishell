/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:04:00 by anogueir          #+#    #+#             */
/*   Updated: 2025/06/12 12:04:01 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_process	*new_process(char *cmd_seq)
{
	t_process	*process;

	process = malloc(sizeof(t_process));
	if (!process)
		return (NULL);
	ft_bzero(process, sizeof(t_process));
	process->cmd_seq = cmd_seq;
	process->next = NULL;
	return (process);
}

void	add_process(t_process **lst, t_process *new)
{
	t_process	*tmp;

	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

/*void	malloc_process(size_t bytes, t_process)
{
	void	*malloced_space;

	malloced_space = malloc(bytes);
	if (!malloced_space)
	{
		// SAFE EXIT
		exit(1);
	}
	return (malloced_space);
}*/
