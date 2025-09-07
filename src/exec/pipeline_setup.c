/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:02:30 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/07 18:20:14 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	setup_input_redirect(t_process *process, t_pipeline *pipeline,
			int process_index)
{
	t_pipe	*cur_pipe;
	int		i;

	if (process->input_file)
		process->fdin = open(process->input_file, O_RDONLY);
	else if (process_index == 0)
		process->fdin = 0;
	else
	{
		cur_pipe = pipeline->pipes;
		i = process_index - 1;
		while (i > 0 && cur_pipe)
		{
			cur_pipe = cur_pipe->next;
			i--;
		}
		if (cur_pipe)
			process->fdin = cur_pipe->read_fd;
	}
}

static void	setup_output_file(t_process *process)
{
	if (process->append_flag)
		process->fdout = open(process->output_file,
				O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		process->fdout = open(process->output_file,
				O_WRONLY | O_CREAT | O_TRUNC, 0666);
}

static void	setup_output_redirect(t_process *process, t_pipeline *pipeline,
			int process_index)
{
	t_pipe	*cur_pipe;
	int		i;

	if (process->output_file)
		setup_output_file(process);
	else if (process_index == pipeline->process_count - 1)
		process->fdout = 1;
	else
	{
		cur_pipe = pipeline->pipes;
		i = process_index;
		while (i > 0 && cur_pipe)
		{
			cur_pipe = cur_pipe->next;
			i--;
		}
		if (cur_pipe)
			process->fdout = cur_pipe->write_fd;
	}
}

void	setup_process_redirects(t_process *process, t_pipeline *pipeline,
			int process_index)
{
	setup_input_redirect(process, pipeline, process_index);
	setup_output_redirect(process, pipeline, process_index);
}
