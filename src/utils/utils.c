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

int	is_between_quotes(const char *str, int pos)
{
	int	i;
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (i < pos && str[i])
	{
		if (str[i] == DOUBLE_QUOTE && !single_quote)
			double_quote = !double_quote;
		else if (str[i] == SINGLE_QUOTE && !double_quote)
			single_quote = !single_quote;
		i++;
	}
	return (double_quote || single_quote);
}

char	*get_str(char *str, int *i, t_minishell *minishell)
{
	int	start;
	char	*result;

	start = *i;
    while (str[*i] && !ft_isspace(str[*i]))
        (*i)++;
    result = ft_substr(str, start, *i - start);
	if (!result)
		safe_exit(minishell);
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
