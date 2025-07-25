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
		envp_copy[i] = ft_strjoin(current->var_name, "=");
		envp_copy[i] = ft_strjoin_free(envp_copy[i], current->var_cont);
		i++;
		current = current->next;
	}
	envp_copy[i] = NULL;
	return (envp_copy);
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
		variables = safe_malloc(sizeof(t_env_vars));
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
		printf("env_list[%d]: %s=%s\n", i, current->var_name,
			current->var_cont);
		current = current->next;
		i++;
	}
}
