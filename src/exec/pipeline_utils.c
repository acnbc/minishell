/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:02:30 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/07 16:54:30 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_pipeline_pipes(t_pipeline *pipeline)
{
	t_pipe	*current;

	current = pipeline->pipes;
	while (current)
	{
		close(current->read_fd);
		close(current->write_fd);
		current = current->next;
	}
}

void	close_unused_pipes(t_pipeline *pipeline, t_process *current)
{
	t_pipe	*pipe;
	int		i;

	pipe = pipeline->pipes;
	i = 0;
	while (pipe)
	{
		if (current->fdin != pipe->read_fd)
			close(pipe->read_fd);
		if (current->fdout != pipe->write_fd)
			close(pipe->write_fd);
		pipe = pipe->next;
		i++;
	}
}

void	free_pipeline(t_pipeline *pipeline)
{
	t_pipe	*current;
	t_pipe	*next;

	if (!pipeline)
		return ;
	current = pipeline->pipes;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(pipeline);
}

void	execute_pipeline(t_minishell *mini)
{
	t_process	*current;
	int			process_index;

	mini->pipeline = create_pipeline(mini->process_list);
	if (!mini->pipeline)
		return ;
	current = mini->process_list;
	process_index = 0;
	while (current)
	{
		setup_process_redirects(current, mini->pipeline, process_index);
		current = current->next;
		process_index++;
	}
	execute_processes(mini);
	close_pipeline_pipes(mini->pipeline);
	wait_all_processes(mini->process_list);
	close_builtin_fds(mini->process_list);
	close_process_fds(mini->process_list);
	free_pipeline(mini->pipeline);
	mini->pipeline = NULL;
}
