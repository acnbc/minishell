/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:30:10 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/06 00:01:50 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	cleanup_process_fds(t_process *p)
{
	if (p->fdin != -1 && p->fdin != 0 && p->fdin != 1 && p->fdin != 2)
	{
		close(p->fdin);
		p->fdin = -1;
	}
	if (p->fdout != -1 && p->fdout != 0 && p->fdout != 1 && p->fdout != 2)
	{
		close(p->fdout);
		p->fdout = -1;
	}
	if (p->pipe_fd[0] != -1)
	{
		close(p->pipe_fd[0]);
		p->pipe_fd[0] = -1;
	}
	if (p->pipe_fd[1] != -1)
	{
		close(p->pipe_fd[1]);
		p->pipe_fd[1] = -1;
	}
}

static void	cleanup_exec_vars(t_minishell *mini)
{
	if (mini->exec_vars)
	{
		if (mini->exec_vars->tmpin != -1)
		{
			close(mini->exec_vars->tmpin);
			mini->exec_vars->tmpin = -1;
		}
		if (mini->exec_vars->tmpout != -1)
		{
			close(mini->exec_vars->tmpout);
			mini->exec_vars->tmpout = -1;
		}
	}
}

void	cleanup_all_fds(t_minishell *mini)
{
	t_process	*p;

	p = mini->process_list;
	while (p)
	{
		cleanup_process_fds(p);
		p = p->next;
	}
	cleanup_exec_vars(mini);
}
