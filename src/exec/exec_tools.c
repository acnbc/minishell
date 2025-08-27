/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 16:07:11 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/26 20:51:14 by anogueir         ###   ########.fr       */
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

void	open_pipes(t_minishell *mini)
{
	t_process	*p;
	t_exec_vars	*e;

	p = mini->cur_proc;
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
}

void	exec_builtin(t_minishell *mini)
{
	t_process	*p;

	p = mini->cur_proc;
	if (ft_strncmp(p->args[0], "cd", ft_strlen(p->args[0])) == 0)
		g_exit_status = ft_cd(mini, mini->env_list);
	else if (ft_strncmp(p->args[0], "echo", ft_strlen(p->args[0])) == 0)
		g_exit_status = ft_echo(p->args, p->fdout);
	else if (ft_strncmp(p->args[0], "pwd", ft_strlen(p->args[0])) == 0)
		g_exit_status = ft_pwd(mini->cur_proc, mini->env_list);
	else if (ft_strncmp(p->args[0], "export", ft_strlen(p->args[0])) == 0)
		g_exit_status = ft_export(mini->env_list, p->args);
	else if (ft_strncmp(p->args[0], "unset", ft_strlen(p->args[0])) == 0)
		g_exit_status = ft_unset(mini->env_list, p->args);
	else if (ft_strncmp(p->args[0], "env", ft_strlen(p->args[0])) == 0)
		g_exit_status = ft_env(mini->env_list, p->fdout);
}
