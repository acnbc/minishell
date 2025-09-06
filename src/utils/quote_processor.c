/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_processor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 08:30:00 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/06 14:36:31 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*process_single_quotes(const char *seg, int *j)
{
	int		start;
	int		k;

	(*j)++;
	start = *j;
	k = *j;
	while (seg[k] && seg[k] != SINGLE_QUOTE)
		k++;
	*j = k;
	if (seg[*j] == SINGLE_QUOTE)
		(*j)++;
	return (ft_substr(seg, start, k - start));
}

char	*expand_variable(t_minishell *mini, const char *segment, int *j)
{
	int		k;
	char	*var;
	char	*val;

	k = *j + 1;
	if (segment[k] == '?')
		k++;
	else
		while (segment[k] && is_stopchar(segment[k]))
			k++;
	var = ft_substr(segment, *j, k - *j);
	val = expansion(mini, var);
	free(var);
	*j = k;
	return (val);
}

char	*expand_literal(const char *segment, int *j)
{
	int		k;
	char	*literal;

	k = *j;
	while (segment[k] && segment[k] != SINGLE_QUOTE
		&& segment[k] != DOUBLE_QUOTE && segment[k] != '$')
		k++;
	literal = ft_substr(segment, *j, k - *j);
	*j = k;
	return (literal);
}
