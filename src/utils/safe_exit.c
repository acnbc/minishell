/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:37:39 by anogueir          #+#    #+#             */
/*   Updated: 2025/07/03 12:37:41 by anogueir         ###   ########.fr       */
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
		if (process_list->heredoc_delimiter)
			free(process_list->heredoc_delimiter);
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

void	safe_exit(t_minishell *minishell)
{
	if (!minishell)
		exit(EXIT_FAILURE);
	if (minishell->input)
	{
		free(minishell->input);
		minishell->input = NULL;
	}
	if (minishell->process_list)
	{
		free_process_list(minishell->process_list);
		minishell->process_list = NULL;
	}
	if (minishell->env_list)
	{
		free_env_list(minishell->env_list);
		minishell->env_list = NULL;
	}
	if (minishell->envp_copy)
	{
		free_env(minishell->envp_copy);
		minishell->envp_copy = NULL;
	}
	free(minishell);
	exit(EXIT_SUCCESS);
}

void	flush(t_minishell *minishell)
{
	free(minishell->input);
	if (minishell->process_list)
	{
		free_process_list(minishell->process_list);
		minishell->process_list = NULL;
	}
	if (minishell->envp_copy)
	{
		free_env(minishell->envp_copy);
		minishell->envp_copy = NULL;
	}
}