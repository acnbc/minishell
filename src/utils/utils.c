/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:45:41 by anogueir          #+#    #+#             */
/*   Updated: 2025/07/03 12:45:42 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_str(char *str, int *i)
{
	int	start;
	char	*result;

	start = *i;
    while (str[*i] && !ft_isspace(str[*i]))
        (*i)++;
    result = ft_substr(str, start, *i - start);
	if (!result)
	{
		// SAFE EXIT
		exit(1);
	}
	return (result);
}

int	skip_spaces(char *str, int *i)
{
	while (str[*i] && ft_isspace(str[*i]))
	{
		printf("em skip spaces, i = %d\n", *i);
		(*i)++;
	}
	return (*i);
}

int	ft_isspace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

char	*ft_strjoin_free(char *s1, char *s2)
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
