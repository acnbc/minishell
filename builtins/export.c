/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:46:54 by abouchat          #+#    #+#             */
/*   Updated: 2025/07/11 18:04:03 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export(char *arg_name, char *arg_cont, t_env *env_list)
{
	t_env	*temp_node;

	if (arg_name == NULL)
		return ;
	if (find_env_var(arg_name, env_list))
	{
		temp_node = find_env_var(arg_name, env_list);
		temp_node->var_cont = arg_cont;
	}
	else
	{
		temp_node = env_lstnew(ft_strdup(arg_name), ft_strdup(arg_cont));
		env_lstadd_back(&env_list, temp_node);
	}
}

t_env	*find_env_var(char *var, t_env *env_list)
{
	t_env	*curr;

	curr = env_list;
	while (curr)
	{
		if (!ft_strncmp(var, curr->var_name, ft_strlen(var)))
			break ;
		curr = curr->next;
	}
	return (curr);
}

t_env	*env_lstnew(char *var_name, char *var_cont)
{
	t_env	*new_node;

	new_node = (t_env *)safe_malloc(sizeof(t_env));
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
