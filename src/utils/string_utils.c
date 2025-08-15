/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:23:30 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/15 08:41:22 by anogueir         ###   ########.fr       */
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

char	*get_str(char *str, int *i, t_minishell *mini)
{
	int		start;
	char	*result;

	if (str[*i] == '\0')
		return (NULL);
	start = *i;
	while (str[*i] && !ft_isspace(str[*i]))
		(*i)++;
	result = ft_substr(str, start, *i - start);
	if (!result)
		safe_exit(mini);
	return (result);
}

int	skip_spaces(char *str, int *i)
{
	while (str[*i] && ft_isspace(str[*i]))
		(*i)++;
	return (*i);
}

int	ft_isspace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

char	*ft_substr_safe(char *s, unsigned int start, size_t len,
		t_minishell *mini)
{
	char	*substr;

	substr = ft_substr(s, start, len);
	if (!substr)
		safe_exit(mini);
	return (substr);
}
