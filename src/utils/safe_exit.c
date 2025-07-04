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

char	*ft_substr_safe(char *s, unsigned int start, size_t len, t_minishell *minishell)
{
    char	*substr;

    substr = ft_substr(s, start, len);
	if (!substr)
	{
		// safe_exit;
		free (minishell->current_process);
		return (NULL);
	}
    return (substr);
}

void	free_process_list(t_process *process_list)
{
	t_process	*tmp;

	if (!process_list)
		return ;
	while (process_list)
	{
		tmp = process_list->next;
		free(process_list->cmd_seq);
		free(process_list);
		process_list = tmp;
	}
}

void	free_env_list(t_env *env_list)
{
	t_env	*tmp;

	if (!env_list)
		return ;
	while (env_list)
	{
		tmp = env_list->next;
		free(env_list->env_var);
		free(env_list);
		env_list = tmp;
	}
}

void	free_env(char **envp_copy, int i)
{
	if (!envp_copy)
		return ;
	while (--i >= 0)
		free(envp_copy[i]);
	free(envp_copy);
}
