/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:11:35 by abouchat          #+#    #+#             */
/*   Updated: 2025/07/09 18:38:33 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*env_list(char *envp[])
{
	t_env	*env_list;
	t_env	*new_node;
	int		i;
	char	**split_str;

	if (!envp || !*envp)
		return (NULL);
	env_list = NULL;
	i = -1;
	while (envp[++i])
	{
		split_str = ft_split(envp[i], '=');
		if (split_str == NULL)
			return (NULL);
		new_node = env_lstnew(ft_strdup(split_str[0]), ft_strdup(split_str[1]));
		split_free(split_str, 1);
		if (!new_node)
		{
			free_env_list(env_list);
			return (NULL);
		}
		env_lstadd_back(&env_list, new_node);
	}
	return (env_list);
}

void	*safe_malloc(size_t bytes)
{
	void	*malloced_space;

	malloced_space = malloc(bytes);
	if (!malloced_space)
	{
		// SAFE EXIT
		exit(1);
	}
	ft_bzero(malloced_space, bytes);
	if (bytes == 0)
	{
		free(malloced_space);
		return (NULL);
	}
	return (malloced_space);
}

void	free_env_list(t_env *env_list)
{
	t_env	*tmp;

	if (!env_list)
		return ;
	while (env_list)
	{
		tmp = env_list->next;
		free(env_list->var_cont);
		free(env_list->var_name);
		free(env_list);
		env_list = tmp;
	}
}
