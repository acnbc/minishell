/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:45:41 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/15 08:23:04 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*strjoin_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (joined);
}

void	*safe_malloc(size_t bytes)
{
	void	*malloced_space;

	malloced_space = ft_calloc(1, bytes);
	if (!malloced_space)
	{
		// SAFE EXIT
		exit(1);
	}
	if (bytes == 0)
	{
		free(malloced_space);
		return (NULL);
	}
	return (malloced_space);
}

char	**paths(t_env *env_list)
{
	while (env_list)
	{
		if (ft_strncmp(env_list->var_name, "PATH", 4) == 0)
		{
			if (env_list->var_cont)
				return (ft_split(env_list->var_cont, ':'));
			else
				return (NULL);
		}
		env_list = env_list->next;
	}
	return (NULL);
}

char	*path_name(char **paths, char *command)
{
	char	*path;
	char	*final_path;
	int		i;

	path = NULL;
	final_path = NULL;
	i = -1;
	while (paths[++i] != NULL)
	{
		path = ft_strjoin(paths[i], "/");
		final_path = ft_strjoin(path, command);
		free(path);
		if (access(final_path, X_OK) == 0)
			return (final_path);
		free(final_path);
	}
	return (NULL);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}
