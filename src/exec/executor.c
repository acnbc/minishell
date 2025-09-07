/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:20:57 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/07 15:14:00 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_processes(t_minishell *mini)
{
	t_process	*p;

	p = mini->process_list;
	while (p)
	{
		mini->cur_proc = p;
		if (p->tokens && p->tokens->type == BUILTIN)
			execute_builtin_command(mini, p);
		else if (p->tokens && p->tokens->type == CMD)
			create_forks(mini);
		else
			handle_invalid_command(p);
		p = p->next;
	}
}

void	execute_command(t_minishell *mini)
{
	t_exec_vars	e;
	t_process	*p;

	ft_memset(&e, -1, sizeof(t_exec_vars));
	p = mini->process_list;
	e.tmpin = dup(STDIN_FILENO);
	e.tmpout = dup(STDOUT_FILENO);
	mini->exec_vars = &e;
	signal(SIGQUIT, exec_signal_handler);
	signal(SIGINT, exec_signal_handler);
	while (p)
	{
		mini->cur_proc = p;
		get_redirect_in(mini);
		get_redirect_out(mini);
		p = p->next;
	}
	execute_processes(mini);
	cleanup_pipes(mini);
	wait_all_processes(mini->process_list);
	close_process_fds(mini->process_list);
	dup2(e.tmpin, 0);
	dup2(e.tmpout, 1);
	close(e.tmpin);
	close(e.tmpout);
	mini->exec_vars = NULL;
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
