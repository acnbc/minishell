/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:20:57 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/15 09:08:23 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_all_processes(t_process *head)
{
	t_process	*cur;

	cur = head;
	while (cur)
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
		cur = cur->next;
	}
}

static void	close_fds(t_process *p)
{
	if (p->fdin != -1)
		close(p->fdin);
	if (p->fdout != -1)
		close(p->fdout);
}

static void	dup2_safe(t_minishell *mini, int *fd, int dup2_fd,
		const char *error_message)
{
	dup2(*fd, dup2_fd);
	if (*fd == -1)
	{
		perror(error_message);
		safe_exit(mini);
	}
}

static void	create_forks(t_minishell *mini)
{
	t_process	*p;

	p = mini->current_process;
	p->pid = fork();
	if (p->pid < 0)
	{
		perror("fork");
		safe_exit(mini);
	}
	if (p->pid == 0)
	{
		if (p->fdin != 0)
		{
			dup2_safe(mini, &p->fdin, 0, "dup2 (stdin)");
			close(p->fdin);
		}
		if (p->fdout != 1)
		{
			dup2_safe(mini, &p->fdout, 1, "dup2 (stdout)");
			close(p->fdout);
		}
		execve(p->path, p->args, mini->envp_copy);
		perror("execve");
		exit(1);
	}
}

static void	open_pipes(t_minishell *mini)
{
	t_process	*p;
	t_exec_vars	*e;

	p = mini->current_process;
	e = mini->exec_vars;
	if (pipe(e->fdpipe) == -1)
	{
		perror("pipe");
		safe_exit(mini);
	}
	if (!p->output_file)
		p->fdout = e->fdpipe[1];
	if (p->next->fdin == -1 && !p->next->input_file)
		p->next->fdin = e->fdpipe[0];
	else
		close(e->fdpipe[0]);
}

static void	dup_safe(t_minishell *mini, int *fd, int dup_fd,
		const char *error_message)
{
	*fd = dup(dup_fd);
	if (*fd == -1)
	{
		perror(error_message);
		safe_exit(mini);
	}
}

static void	get_redirect_in(t_minishell *mini)
{
	t_process	*p;

	p = mini->current_process;
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

static void	get_redirect_out(t_minishell *mini)
{
	t_process	*p;

	p = mini->current_process;
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

void	execute_command(t_minishell *mini)
{
	t_exec_vars	e;
	t_process	*p;

	ft_memset(&e, -1, sizeof(t_exec_vars));
	dup_safe(mini, &e.tmpin, 0, "dup (stdin)");
	dup_safe(mini, &e.tmpout, 1, "dup (stdout)");
	p = mini->process_list;
	mini->exec_vars = &e;
	while (p)
	{
		mini->current_process = p;
		get_redirect_in(mini);
		get_redirect_out(mini);
		create_forks(mini);
		close_fds(p);
		p = p->next;
	}
	dup2_safe(mini, &e.tmpin, 0, "dup2 (stdin)");
	dup2_safe(mini, &e.tmpout, 1, "dup2 (stdout)");
	close(e.tmpin);
	close(e.tmpout);
	wait_all_processes(mini->process_list);
}

void	executor(t_minishell *mini)
{
	if (mini->envp_copy)
		free_env(mini->envp_copy);
	mini->envp_copy = copy_envp(mini->env_list);
	if (!get_args(mini->process_list))
		return ;
	execute_command(mini);
	unlink_heredoc_files(mini);
}
