/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 16:39:34 by abouchat          #+#    #+#             */
/*   Updated: 2025/08/15 08:46:30 by anogueir         ###   ########.fr       */
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
	while (1)
	{
		if (!mini_shell(mini))
			break ;
	}
	return (0);
}
