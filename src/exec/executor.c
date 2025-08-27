/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:20:57 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/27 10:46:37 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	child_process(t_minishell *mini, t_process *p)
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
	if (mini->exec_vars->fdpipe[0] != -1)
		close(mini->exec_vars->fdpipe[0]);
	if (mini->exec_vars->fdpipe[1] != -1)
		close(mini->exec_vars->fdpipe[1]);
	execve(p->path, p->args, mini->envp_copy);
	perror("execve");
	safe_exit(mini);
}

static void	parent_process(t_minishell *mini, t_process *p)
{
	if (p->fdin != -1 && p->fdin != mini->exec_vars->tmpin)
	{
		close(p->fdin);
		p->fdin = -1;
	}
	if (p->fdout != -1 && p->fdout != mini->exec_vars->tmpout)
	{
		close(p->fdout);
		p->fdout = -1;
	}
}

static void	create_forks(t_minishell *mini)
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
	else
		parent_process(mini, p);
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
	signal(SIGQUIT, exec_signal_handler);
	signal(SIGINT, exec_signal_handler);
	while (p)
	{
		mini->cur_proc = p;
		get_redirect_in(mini);
		get_redirect_out(mini);
		if (p->tokens->type == BUILTIN)
			exec_builtin(mini);
		else
			create_forks(mini);
		p = p->next;
	}
	close_fds(mini->process_list, &e, mini);
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
}
