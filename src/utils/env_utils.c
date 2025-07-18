/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:37:23 by anogueir          #+#    #+#             */
/*   Updated: 2025/07/03 12:37:25 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**copy_envp(t_env *env_list)
{
	char	**envp_copy;
	t_env	*current;
	int		i;

	if (!env_list)
		return (NULL);
	current = env_list;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	envp_copy = (char **)safe_malloc((i + 1) * sizeof(char *));
	current = env_list;
	i = 0;
	while (current)
	{
		envp_copy[i++] = ft_strdup(current->env_var);
		current = current->next;
	}
	envp_copy[i] = NULL;
	return (envp_copy);
}

t_env	*env_lstnew(char *env_var)
{
	t_env	*new_node;

	new_node = (t_env *)safe_malloc(sizeof(t_env));
	new_node->env_var = env_var;
	new_node->next = NULL;
	return (new_node);
}

void	env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*curr;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	curr = *lst;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}

t_env	*env_list(char *envp[])
{
	t_env	*env_list;
	t_env	*new_node;
	int		i;

	if (!envp || !*envp)
		return (NULL);
	env_list = NULL;
	i = -1;
	while (envp[++i])
	{
		new_node = env_lstnew(ft_strdup(envp[i]));
		if (!new_node)
		{
			free_env_list(env_list);
			return (NULL);
		}
		env_lstadd_back(&env_list, new_node);
	}
	return (env_list);
}

void	print_envp(char **envp_copy)
{
	int	i;

	i = 0;
	if (!envp_copy)
		return ;
	while (envp_copy[i])
	{
		printf("envp_copy[%d]: %s\n", i, envp_copy[i]);
		i++;
	}
}

void	print_env_list(t_env *env_list)
{
	t_env	*current;
	int		i;

	current = env_list;
	i = 0;
	while (current)
	{
		printf("env_list[%d]: %s\n", i, current->env_var);
		current = current->next;
		i++;
	}
}