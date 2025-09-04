/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 16:07:11 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/03 21:21:35 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_invalid_command(t_process *p)
{
	struct stat	path_stat;

	if (p->tokens && p->tokens->value)
	{
		if (stat(p->tokens->value, &path_stat) == 0)
		{
			if (S_ISDIR(path_stat.st_mode))
			{
				write(2, "minishell: ", 11);
				write(2, p->tokens->value, ft_strlen(p->tokens->value));
				write(2, ": Is a directory\n", 18);
				g_exit_status = 126;
				return ;
			}
		}
	}
	ft_putstr_fd("minishell: ", 2);	
	if (p->tokens)
		ft_putstr_fd(p->tokens->value, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_exit_status = 127;
}

void	wait_all_processes(t_process *head)
{
	t_process	*cur;

	cur = head;
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
		g_exit_status = ft_pwd(mini->cur_proc);
	else if (ft_strncmp(p->args[0], "export", ft_strlen(p->args[0])) == 0)
		g_exit_status = ft_export(mini->env_list, p->args);
	else if (ft_strncmp(p->args[0], "unset", ft_strlen(p->args[0])) == 0)
		g_exit_status = ft_unset(mini->env_list, p->args);
	else if (ft_strncmp(p->args[0], "env", ft_strlen(p->args[0])) == 0)
		g_exit_status = ft_env(mini->env_list, p->fdout);
	else if (ft_strncmp(p->args[0], "exit", ft_strlen(p->args[0])) == 0)
	{
		g_exit_status = ft_exit(p->args);
		safe_exit(mini);
	}
}
