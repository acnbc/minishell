/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:30:10 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/24 13:48:49 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	close_process_fds(t_process *p_list)
{
	t_process	*p;

	p = p_list;
	while (p)
	{
		if (p->fdin != -1)
		{
			close(p->fdin);
			p->fdin = -1;
		}
		if (p->fdout != -1)
		{
			close(p->fdout);
			p->fdout = -1;
		}
		p = p->next;
	}
}

static void	close_pipe_fds(t_exec_vars *e)
{
	if (e->fdpipe[0] != -1)
	{
		close(e->fdpipe[0]);
		e->fdpipe[0] = -1;
	}
	if (e->fdpipe[1] != -1)
	{
		close(e->fdpipe[1]);
		e->fdpipe[1] = -1;
	}
}

void	close_fds(t_process *p_list, t_exec_vars *e, t_minishell *mini)
{
	close_process_fds(p_list);
	close_pipe_fds(e);
	dup2_safe(mini, &e->tmpin, 0, "dup2 (stdin)");
	dup2_safe(mini, &e->tmpout, 1, "dup2 (stdout)");
	close(e->tmpin);
	close(e->tmpout);
}

void	get_redirect_in(t_minishell *mini)
{
	t_process	*p;

	p = mini->cur_proc;
	if (p->fdin == -1)
	{
		if (p->input_file)
		{
			p->fdin = open(p->input_file, O_RDONLY);
			if (p->fdin == -1)
			{
				perror(p->input_file);
				p->exit_signal = 1;
				return ;
			}
		}
		else
			dup_safe(mini, &p->fdin, mini->exec_vars->tmpin, "dup (stdin)");
	}
}

void	get_redirect_out(t_minishell *mini)
{
	t_process	*p;

	p = mini->cur_proc;
	if (p->output_file)
	{
		if (p->append_flag)
			p->fdout = open(p->output_file, O_WRONLY | O_CREAT | O_APPEND,
					0666);
		else if (p->redirect_out_flag)
			p->fdout = open(p->output_file, O_WRONLY | O_CREAT | O_TRUNC,
					0666);
		if (p->fdout == -1)
		{
			perror(p->output_file);
			p->exit_signal = 1;
			return ;
		}
	}
	else if (p->next)
		open_pipes(mini);
	else
		dup_safe(mini, &p->fdout, mini->exec_vars->tmpout, "dup (stdout)");
}
