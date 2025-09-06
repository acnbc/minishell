/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:45:00 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/06 16:55:33 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	exec_builtin_with_pipe(t_minishell *mini)
{
	t_process	*p;
	int			pipe_fd[2];
	int			saved_stdout;

	p = mini->cur_proc;
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return ;
	}
	saved_stdout = dup(1);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[1]);
	execute_builtin_command(mini, p);
	dup2(saved_stdout, 1);
	close(saved_stdout);
	if (p->next)
		p->next->fdin = pipe_fd[0];
}
