/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 23:55:00 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/06 16:25:31 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_segment(t_minishell *mini, const char *segment)
{
	char	*expanded;
	int		j;

	expanded = NULL;
	j = 0;
	while (segment[j])
	{
		if (segment[j] == SINGLE_QUOTE)
			expanded = strjoin_free(expanded,
					process_single_quotes(segment, &j));
		else if (segment[j] == DOUBLE_QUOTE)
			expanded = strjoin_free(expanded,
					process_double_quotes(mini, segment, &j));
		else if (segment[j] == '$')
			expanded = strjoin_free(expanded,
					expand_variable(mini, segment, &j));
		else
			expanded = strjoin_free(expanded,
					expand_literal(segment, &j));
	}
	if (!expanded)
		expanded = ft_strdup("");
	return (expanded);
}

static void	process_double_quote_var(t_minishell *mini, const char *seg,
			int *j, char **res)
{
	int		k;
	char	*result;
	char	*expansion_result;

	k = *j + 1;
	if (seg[k] == '?')
		k++;
	else
		while (seg[k] && is_stopchar(seg[k]))
			k++;
	result = ft_substr(seg, *j, k - *j);
	expansion_result = expansion(mini, result);
	*res = strjoin_free(*res,
			expansion_result);
	free(result);
	*j = k;
}

static void	process_double_quote_literal(const char *seg, int *j, char **res)
{
	int		start;
	char	*result;

	start = *j;
	while (seg[*j] && seg[*j] != DOUBLE_QUOTE && seg[*j] != '$')
		(*j)++;
	result = ft_substr(seg, start, *j - start);
	*res = strjoin_free(*res, result);
}

char	*process_double_quotes(t_minishell *mini, const char *seg, int *j)
{
	char	*res;

	res = NULL;
	(*j)++;
	while (seg[*j] && seg[*j] != DOUBLE_QUOTE)
	{
		if (seg[*j] == '$')
			process_double_quote_var(mini, seg, j, &res);
		else
			process_double_quote_literal(seg, j, &res);
	}
	if (seg[*j] == DOUBLE_QUOTE)
		(*j)++;
	if (!res)
		res = ft_strdup("");
	return (res);
}

char	*process_quoted_string(t_minishell *mini, char *cmd_seq, int *i)
{
	int		start;
	int		len;
	char	*segment;
	char	*result;

	start = *i;
	len = ft_strlen(cmd_seq);
	while (*i < len && !ft_isspace(cmd_seq[*i]))
		(*i)++;
	segment = ft_substr(cmd_seq, start, *i - start);
	result = expand_segment(mini, segment);
	free(segment);
	return (result);
}
