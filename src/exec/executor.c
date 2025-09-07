/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:20:57 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/07 15:51:47 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_processes(t_minishell *mini)
{
	t_process	*current;

	current = mini->process_list;
	while (current)
	{
		mini->cur_proc = current;
		if (current->tokens && current->tokens->type == CMD)
			create_forks(mini);
		else if (current->tokens && current->tokens->type == BUILTIN)
			execute_builtin_in_pipeline(mini, current);
		else
			handle_invalid_command(current);
		current = current->next;
	}
}

void	execute_command(t_minishell *mini)
{
	t_exec_vars	e;

	ft_memset(&e, -1, sizeof(t_exec_vars));
	e.tmpin = dup(STDIN_FILENO);
	e.tmpout = dup(STDOUT_FILENO);
	mini->exec_vars = &e;
	signal(SIGQUIT, exec_signal_handler);
	signal(SIGINT, exec_signal_handler);
	execute_pipeline(mini);
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
