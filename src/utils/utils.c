/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:39:20 by anogueir          #+#    #+#             */
/*   Updated: 2025/06/17 09:39:22 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
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

void	free_env(char **envp_copy, int i)
{
	while (--i >= 0)
		free(envp_copy[i]);
	free(envp_copy);
}
