/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:02:30 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/07 16:54:40 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_pipe	*create_pipe_node(void)
{
	t_pipe	*pipe_node;
	int		pipe_fds[2];

	pipe_node = malloc(sizeof(t_pipe));
	if (!pipe_node)
		return (NULL);
	if (pipe(pipe_fds) == -1)
	{
		perror("pipe");
		free(pipe_node);
		return (NULL);
	}
	pipe_node->read_fd = pipe_fds[0];
	pipe_node->write_fd = pipe_fds[1];
	pipe_node->next = NULL;
	return (pipe_node);
}

static void	count_processes_and_pipes(t_process *process_list,
		int *process_count, int *pipe_count)
{
	t_process	*current;

	*process_count = 0;
	*pipe_count = 0;
	current = process_list;
	while (current)
	{
		(*process_count)++;
		if (current->next)
			(*pipe_count)++;
		current = current->next;
	}
}

t_pipeline	*create_pipeline(t_process *process_list)
{
	t_pipeline	*pipeline;
	t_pipe		*pipe_node;
	t_process	*current;
	int			pipe_count;
	int			process_count;

	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		return (NULL);
	pipeline->pipes = NULL;
	pipeline->processes = process_list;
	count_processes_and_pipes(process_list, &process_count, &pipe_count);
	pipeline->process_count = process_count;
	pipeline->pipe_count = pipe_count;
	current = process_list;
	while (current && current->next)
	{
		pipe_node = create_pipe_node();
		if (!pipe_node)
			return (NULL);
		pipe_node->next = pipeline->pipes;
		pipeline->pipes = pipe_node;
		current = current->next;
	}
	return (pipeline);
}
