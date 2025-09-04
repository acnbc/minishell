/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 16:07:11 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/01 19:31:57 by anogueir         ###   ########.fr       */
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

void	handle_invalid_command(t_process *p)
{
	if (p->tokens && p->tokens->value)
	{
		if (is_directory(p->tokens->value))
			return ;
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
}
