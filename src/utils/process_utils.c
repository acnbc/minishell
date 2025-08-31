/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:04:00 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/31 14:15:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_process_list(t_process *process_list)
{
	t_process	*tmp;

	if (!process_list)
		return ;
	while (process_list)
	{
		tmp = process_list->next;
		if (process_list->cmd_seq)
			free(process_list->cmd_seq);
		if (process_list->input_file)
			free(process_list->input_file);
		if (process_list->output_file)
			free(process_list->output_file);
		if (process_list->delimiter)
			free(process_list->delimiter);
		if (process_list->path)
			free(process_list->path);
		if (process_list->tokens)
			free_token_list(process_list->tokens);
		if (process_list->args)
			free_matrix(process_list->args);
		free(process_list);
		process_list = tmp;
	}
}

t_process	*new_process(char *cmd_seq)
{
	t_process	*process;

	process = (t_process *)ft_calloc(0, sizeof(t_process));
	if (!process)
		return (NULL);
	process->cmd_seq = cmd_seq;
	process->fdin = -1;
	process->fdout = -1;
	process->next = NULL;
	process->path = NULL;
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
