/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 16:39:34 by abouchat          #+#    #+#             */
/*   Updated: 2025/06/08 16:48:07 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status;

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	g_exit_status = 0;
	minishell = safe_malloc(sizeof(t_minishell));
	minishell->env_list = env_list(envp);
	minishell->process_list = NULL;
	while (1)
	{
		if (!mini_shell(minishell))
			break ;
	}
	return (0);
}
