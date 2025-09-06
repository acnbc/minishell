/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 23:35:00 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/05 23:42:14 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_other_pipes(t_minishell *mini, t_process *p)
{
	t_process	*tmp;

	tmp = mini->process_list;
	while (tmp)
	{
		if (tmp != p)
		{
			if (tmp->pipe_fd[0] != -1)
				close(tmp->pipe_fd[0]);
			if (tmp->pipe_fd[1] != -1)
				close(tmp->pipe_fd[1]);
		}
		tmp = tmp->next;
	}
}

void	setup_redirects(t_process *p)
{
	if (p->fdin != -1 && p->fdin != 0)
	{
		if (dup2(p->fdin, 0) == -1)
		{
			perror("dup2 (stdin)");
			exit(127);
		}
		close(p->fdin);
	}
	if (p->fdout != -1 && p->fdout != 1)
	{
		if (dup2(p->fdout, 1) == -1)
		{
			perror("dup2 (stdout)");
			exit(127);
		}
		close(p->fdout);
	}
}

void	child_process(t_minishell *mini, t_process *p)
{
	setup_redirects(p);
	close_other_pipes(mini, p);
	if (p->tokens && p->tokens->type == BUILTIN)
	{
		exec_builtin(mini);
		exit(g_exit_status);
	}
	else
	{
		execve(p->path, p->args, mini->envp_copy);
		perror("execve");
		exit(127);
	}
}

void	create_forks(t_minishell *mini)
{
	t_process	*p;

	p = mini->cur_proc;
	p->pid = fork();
	if (p->pid < 0)
	{
		perror("fork");
		safe_exit(mini);
	}
	if (p->pid == 0)
		child_process(mini, p);
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
