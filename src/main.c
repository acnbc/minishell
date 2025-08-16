/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 16:39:34 by abouchat          #+#    #+#             */
/*   Updated: 2025/08/16 12:34:24 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status;

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	*mini;

	(void)argc;
	(void)argv;
	g_exit_status = 0;
	mini = safe_malloc(sizeof(t_minishell));
	mini->env_list = env_list(envp);
	mini->process_list = NULL;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	while (1)
	{
		if (!mini_shell(mini))
			break ;
	}
	return (0);
}
