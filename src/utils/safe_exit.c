/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:37:39 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/03 21:12:52 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	safe_env_list_exit(t_env_vars *vars, t_env *env_list)
{
	free(vars->var_name);
	free(vars->var_cont);
	free(vars->equal_sign);
	free_env_list(env_list);
	exit(1);
}

void	free_env_list(t_env *env_list)
{
	t_env	*tmp;

	if (!env_list)
		return ;
	while (env_list)
	{
		tmp = env_list->next;
		if (env_list->var_name)
			free(env_list->var_name);
		if (env_list->var_cont)
			free(env_list->var_cont);
		free(env_list);
		env_list = tmp;
	}
}

void	free_env(char **envp_copy)
{
	int	i;

	if (!envp_copy)
		return ;
	i = 0;
	while (envp_copy[i])
		free(envp_copy[i++]);
	free(envp_copy);
}

void	safe_exit(t_minishell *mini)
{
	if (!mini)
		exit(EXIT_FAILURE);
	if (mini->input)
	{
		free(mini->input);
		mini->input = NULL;
	}
	if (mini->process_list)
	{
		free_process_list(mini->process_list);
		mini->process_list = NULL;
	}
	if (mini->env_list)
	{
		free_env_list(mini->env_list);
		mini->env_list = NULL;
	}
	if (mini->envp_copy)
	{
		free_env(mini->envp_copy);
		mini->envp_copy = NULL;
	}
	free(mini);
	exit(g_exit_status);
}

void	flush(t_minishell *mini)
{
	free(mini->input);
	if (mini->process_list)
	{
		free_process_list(mini->process_list);
		mini->process_list = NULL;
	}
	if (mini->envp_copy)
	{
		free_env(mini->envp_copy);
		mini->envp_copy = NULL;
	}
}
