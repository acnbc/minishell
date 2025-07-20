/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 19:23:30 by anogueir          #+#    #+#             */
/*   Updated: 2025/07/19 19:23:32 by anogueir         ###   ########.fr       */
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
	int		start;
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
