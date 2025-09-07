/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 00:00:00 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/07 15:14:56 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void close_other_pipes(t_minishell *mini, t_process *current)
{
    t_process *p = mini->process_list;
    
    while (p)
    {
        if (p != current)
        {
            if (p->pipe_fd[0] != -1 && p->fdin != p->pipe_fd[0])
            {
                close(p->pipe_fd[0]);
                p->pipe_fd[0] = -1;
            }
            if (p->pipe_fd[1] != -1 && p->fdout != p->pipe_fd[1])
            {
                close(p->pipe_fd[1]);
                p->pipe_fd[1] = -1;
            }
        }
        p = p->next;
    }
}

void	open_pipes(t_minishell *mini)
{
	t_process	*p;

	p = mini->cur_proc;
	if (pipe(p->pipe_fd) == -1)
	{
		perror("pipe");
		safe_exit(mini);
	}
	if (!p->output_file)
		p->fdout = p->pipe_fd[1];
	if (p->next && p->next->fdin == -1 && !p->next->input_file)
		p->next->fdin = p->pipe_fd[0];
}

void	cleanup_pipes(t_minishell *mini)
{
	t_process	*p;

	p = mini->process_list;
	while (p)
	{
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
		p = p->next;
	}
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
	if (p->next && p->tokens)
		open_pipes(mini);
}
