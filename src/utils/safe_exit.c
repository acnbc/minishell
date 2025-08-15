/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:37:39 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/15 09:19:25 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_process_list(t_process *process_list)
{
	t_process	*tmp;

	if (!process_list)
		return ;
	while (process_list)
	{
		tmp = process_list->next;
		if (process_list->cmd_seq)
			free(process_list->cmd_seq);
		if (process_list->input_file)
			free(process_list->input_file);
		if (process_list->output_file)
			free(process_list->output_file);
		if (process_list->delimiter)
			free(process_list->delimiter);
		if (process_list->path)
			free(process_list->path);
		if (process_list->tokens)
			free_token_list(process_list->tokens);
		if (process_list->args)
			free_matrix(process_list->args);
		free(process_list);
		process_list = tmp;
	}
}

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
	exit(EXIT_SUCCESS);
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
