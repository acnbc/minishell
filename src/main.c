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

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	minishell = safe_malloc(sizeof(t_minishell));
	minishell->env_list = env_list(envp);
	// print_env_list(minishell->env_list);
	while (1)
	{
		minishell->input = readline(MINISHELL_PROMPT);
		if (!minishell->input)
			continue ;
		if (ft_strncmp(minishell->input, "exit", 4) == 0)
		{
			free(minishell->input);
			free_env_list(minishell->env_list);
			free_env(minishell->envp_copy, 0);
			free_process_list(minishell->process_list);
			free(minishell);
			printf("exit\n");
			exit(0);
		}
		parser(minishell);
		// printf("%s\n", input);
	}
}
