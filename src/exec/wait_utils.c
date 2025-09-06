/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:45:00 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/06 16:55:59 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	process_exit_status(t_process *cur, int status)
{
	if (WIFEXITED(status))
		cur->exit_signal = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		cur->exit_signal = 128 + WTERMSIG(status);
	else
		cur->exit_signal = -1;
	if (cur->next == NULL)
		g_exit_status = cur->exit_signal;
	cur->pid = 0;
}

static int	count_total_processes(t_process *head)
{
	t_process	*cur;
	int			total;

	total = 0;
	cur = head;
	while (cur)
	{
		if (cur->pid > 0)
			total++;
		cur = cur->next;
	}
	return (total);
}

static int	process_wait_loop(t_process *head)
{
	t_process	*cur;
	int			status;
	int			pid;
	int			completed;

	completed = 0;
	cur = head;
	while (cur)
	{
		if (cur->pid > 0)
		{
			pid = waitpid(cur->pid, &status, WNOHANG);
			if (pid > 0)
			{
				process_exit_status(cur, status);
				completed++;
			}
		}
		cur = cur->next;
	}
	return (completed);
}

void	wait_all_processes(t_process *head)
{
	int	total_processes;
	int	completed_processes;

	total_processes = count_total_processes(head);
	completed_processes = 0;
	while (completed_processes < total_processes)
	{
		completed_processes += process_wait_loop(head);
		usleep(1000);
	}
}
