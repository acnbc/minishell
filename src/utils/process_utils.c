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

#include "../includes/minishell.h"

t_process	*last_process(t_process *proc)
{
	t_process	*curr;

	if (!proc)
		return (NULL);
	curr = proc;
	while (curr != NULL)
	{
		if (curr->next == NULL)
			break ;
		curr = curr->next;
	}
	return (curr);
}

t_process	*new_process(char *cmd_seq)
{
	t_process	*process;

	process = safe_malloc(sizeof(t_process));
	ft_bzero(process, sizeof(t_process));
	process->cmd_seq = cmd_seq;
	process->fdin = -1;
	process->fdout = -1;
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
