/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:46:54 by abouchat          #+#    #+#             */
/*   Updated: 2025/07/09 18:30:31 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export(char *arg, t_env *env_list)
{
	t_env	*temp_node;
	char	**split_str;

	split_str = ft_split(arg, '=');
	if (split_str == NULL)
		return ;
	if (!split_str[1])
	{
		split_free (split_str, 0);
		return ;
	}
	if (find_env_var(split_str[0], env_list))
	{
		temp_node = find_env_var(split_str[0], env_list);
		temp_node->var_cont = split_str[1];
	}
	else
	{
		temp_node = env_lstnew(ft_strdup(split_str[0]), \
		ft_strdup(split_str[1]));
		env_lstadd_back(&env_list, temp_node);
	}
	split_free(split_str, 1);
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
