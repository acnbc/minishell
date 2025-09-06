/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 16:07:11 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/06 17:52:46 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	execute_env_builtin(t_minishell *mini, t_process *p)
{
	int	fd;

	fd = 1;
	if (p->fdout != -1)
		fd = p->fdout;
	g_exit_status = ft_env(mini->env_list, fd);
}

static void	execute_exit_builtin(t_minishell *mini, t_process *p)
{
	g_exit_status = ft_exit(p->args);
	safe_exit(mini);
}

void	execute_builtin_command(t_minishell *mini, t_process *p)
{
	int	fdout;

	fdout = 1;
	if (p->fdout != -1)
		fdout = p->fdout;
	if (ft_strncmp(p->args[0], "cd", ft_strlen(p->args[0])) == 0)
		g_exit_status = ft_cd(mini, mini->env_list);
	else if (ft_strncmp(p->args[0], "echo", ft_strlen(p->args[0])) == 0)
		g_exit_status = ft_echo(p->args, fdout);
	else if (ft_strncmp(p->args[0], "pwd", ft_strlen(p->args[0])) == 0)
		g_exit_status = ft_pwd(p);
	else if (ft_strncmp(p->args[0], "export", ft_strlen(p->args[0])) == 0)
		g_exit_status = ft_export(mini->env_list, p->args);
	else if (ft_strncmp(p->args[0], "unset", ft_strlen(p->args[0])) == 0)
		g_exit_status = ft_unset(mini->env_list, p->args);
	else if (ft_strncmp(p->args[0], "env", ft_strlen(p->args[0])) == 0)
		execute_env_builtin(mini, p);
	else if (ft_strncmp(p->args[0], "exit", ft_strlen(p->args[0])) == 0)
		execute_exit_builtin(mini, p);
}

void	exec_builtin(t_minishell *mini)
{
	t_process	*p;

	p = mini->cur_proc;
	execute_builtin_command(mini, p);
	if (p->fdin != -1 && p->fdin != 0)
	{
		close(p->fdin);
		p->fdin = -1;
	}
	if (p->fdout != -1 && p->fdout != 1)
	{
		close(p->fdout);
		p->fdout = -1;
	}
}
