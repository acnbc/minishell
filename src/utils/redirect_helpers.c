/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 00:00:00 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/06 18:01:07 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	close_process_fds(t_process *p_list)
{
	t_process	*p;

	p = p_list;
	while (p)
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
		p = p->next;
	}
}

static void	close_pipe_fds(t_process *p)
{
	t_process	*tmp;

	tmp = p;
	while (tmp)
	{
		if (tmp->pipe_fd[0] != -1)
		{
			close(tmp->pipe_fd[0]);
			tmp->pipe_fd[0] = -1;
		}
		if (tmp->pipe_fd[1] != -1)
		{
			close(tmp->pipe_fd[1]);
			tmp->pipe_fd[1] = -1;
		}
		tmp = tmp->next;
	}
}

void	close_fds(t_process *p_list)
{
	close_process_fds(p_list);
	close_pipe_fds(p_list);
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
			p->fdout = open(p->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (p->fdout == -1)
		{
			perror(p->output_file);
			p->exit_signal = 1;
			return ;
		}
	}
	if (p->next && p->tokens && p->tokens->type != BUILTIN)
		open_pipes(mini);
}
