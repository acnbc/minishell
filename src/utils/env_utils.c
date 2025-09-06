/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:37:23 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/06 11:57:24 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**copy_envp(t_env *env_list)
{
	char	**copy;
	t_env	*current;
	int		i;

	current = env_list;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	copy = (char **)ft_calloc((i + 1), sizeof(char *));
	if (!copy)
		return (NULL);
	current = env_list;
	i = 0;
	while (current)
	{
		copy[i] = ft_strjoin(current->var_name, "=");
		copy[i] = strjoin_free(copy[i], ft_strdup(current->var_cont));
		i++;
		current = current->next;
	}
	copy[i] = NULL;
	return (copy);
}

static void	env_list_pair(t_env_vars *vars, int i, char *envp[])
{
	if (vars->equal_sign)
	{
		vars->var_name = ft_substr(envp[i], 0, vars->equal_sign - envp[i]);
		vars->var_cont = ft_strdup(vars->equal_sign + 1);
	}
	else
	{
		vars->var_name = ft_strdup(envp[i]);
		vars->var_cont = ft_strdup("");
	}
}

t_env	*env_list(char *envp[])
{
	t_env		*env_list;
	int			i;
	t_env_vars	*variables;

	if (!envp || !*envp)
		return (NULL);
	env_list = NULL;
	i = -1;
	while (envp[++i])
	{
		variables = (t_env_vars *)ft_calloc(1, sizeof(t_env_vars));
		if (!variables)
			return (NULL);
		variables->equal_sign = ft_strchr(envp[i], '=');
		env_list_pair(variables, i, envp);
		if (!variables->var_name || !variables->var_cont)
			safe_env_list_exit(variables, env_list);
		env_lstadd_back(&env_list, env_lstnew(variables->var_name,
				variables->var_cont));
		free(variables);
	}
	return (env_list);
}

t_env	*env_lstnew(char *var_name, char *var_cont)
{
	t_env	*new_node;

	new_node = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->var_name = var_name;
	new_node->var_cont = var_cont;
	new_node->next = NULL;
	new_node->prev = NULL;
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
	new->prev = curr;
}
