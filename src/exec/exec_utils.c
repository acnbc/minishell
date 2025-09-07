/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 23:35:00 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/07 14:34:55 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_directory(char *word)
{
	struct stat	path_stat;

	if (stat(word, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			write(2, "minishell: ", 11);
			write(2, word, ft_strlen(word));
			write(2, ": Is a directory\n", 18);
			g_exit_status = 126;
			return (1);
		}
	}
	return (0);
}

void	wait_all_processes(t_process *p)
{
	t_process	*cur;

	cur = p;
	while (cur)
	{
		if (cur->pid > 0)
		{
			waitpid(cur->pid, &cur->status, 0);
			if (WIFEXITED(cur->status))
				cur->exit_signal = WEXITSTATUS(cur->status);
			else if (WIFSIGNALED(cur->status))
				cur->exit_signal = 128 + WTERMSIG(cur->status);
			else
				cur->exit_signal = -1;
			if (cur->next == NULL)
				g_exit_status = cur->exit_signal;
		}
		cur = cur->next;
	}
}

void	close_process_fds(t_process *p_list)
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

void	child_process(t_minishell *mini, t_process *p)
{
	if (p->fdin != -1 && p->fdin != 0)
	{
		dup2(p->fdin, 0);
		close(p->fdin);
	}
	if (p->fdout != -1 && p->fdout != 1)
	{
		dup2(p->fdout, 1);
		close(p->fdout);
	}
	close_other_pipes(mini, p);
	execve(p->path, p->args, mini->envp_copy);
	perror("execve");
	exit(127);
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

