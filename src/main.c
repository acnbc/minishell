/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 16:39:34 by abouchat          #+#    #+#             */
/*   Updated: 2025/08/30 20:48:16 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status;

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 130;
	}
}

void	exec_signal_handler(int sig)
{
	if (sig == SIGQUIT)
		write(1, "Quit (core dumped)", 19);
	write (1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_done = 1;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	*mini;

	(void)argc;
	(void)argv;
	g_exit_status = 0;
	mini = (t_minishell *)ft_calloc(1, sizeof(t_minishell));
	if (!mini)
		return (1);
	mini->env_list = env_list(envp);
	if (!mini->env_list)
		return (1);
	mini->process_list = NULL;
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signal_handler);
		mini_shell(mini);
		unlink_heredoc_files(mini);
		flush(mini);
	}
	safe_exit(mini);
	return (0);
}
