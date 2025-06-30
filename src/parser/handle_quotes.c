/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:34:11 by anogueir          #+#    #+#             */
/*   Updated: 2025/06/12 19:34:12 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*cut_double_quotes(t_minishell *minishell, int i)
{
	char	*clean_input;
	int		j;

	clean_input = NULL;
	j = i;
	while (minishell->input[i] != DOUBLE_QUOTE && minishell->input[i])
	{
		if (minishell->input[i] == '$')
			clean_input = get_env_var(minishell, &i, &j);
		else
			i++;
	}
	if (j < i)
		clean_input = ft_strjoin(clean_input, ft_substr(minishell->input, j, i
					- j));
	return (clean_input);
}

static char	*cut_single_quotes(t_minishell *minishell, int i)
{
	char	*clean_input;
	int		j;

	clean_input = NULL;
	j = i;
	while (minishell->input[i] != SINGLE_QUOTE && minishell->input[i++])
		;
	clean_input = safe_malloc((i + 1) * sizeof(char));
	clean_input = ft_substr(minishell->input, j, i - j);
	return (clean_input);
}

static int	verify_quote_pair(char *input, char quote, int *i)
{
	int	flag;

	flag = 1;
	while (input[++(*i)] != quote && input[*i])
		;
	if (input[*i] == quote)
		flag = 0;
	return (flag);
}

static int	verify_quote_count(t_minishell *minishell)
{
	int	single_flag;
	int	double_flag;
	int	i;

	single_flag = 0;
	double_flag = 0;
	i = -1;
	while (minishell->input[++i])
	{
		if (minishell->input[i] == SINGLE_QUOTE)
			single_flag = verify_quote_pair(minishell->input, SINGLE_QUOTE, &i);
		if (minishell->input[i] == DOUBLE_QUOTE)
			double_flag = verify_quote_pair(minishell->input, DOUBLE_QUOTE, &i);
	}
	return (single_flag + double_flag);
}

char	*cut_quotes(t_minishell *minishell, int *i, int *j, char quote)
{
	char	*clean_input;

	clean_input = NULL;
	if (*j < *i)
		clean_input = ft_strjoin(clean_input, ft_substr(minishell->input, *j, *i
					- *j));
	if (quote == SINGLE_QUOTE)
	{
		clean_input = ft_strjoin(clean_input, cut_single_quotes(minishell,
					++(*i)));
		while (minishell->input[*i] && minishell->input[*i] != SINGLE_QUOTE)
			(*i)++;
	}
	else
	{
		clean_input = ft_strjoin(clean_input, cut_double_quotes(minishell,
					++(*i)));
		while (minishell->input[*i] && minishell->input[*i] != DOUBLE_QUOTE)
			(*i)++;
	}
	*j = *i + 1;
	return (clean_input);
}

char	*handle_quotes(t_minishell *minishell)
{
	int		i;
	int		j;
	char	*clean_input;

	i = -1;
	j = 0;
	clean_input = NULL;
	if (verify_quote_count(minishell))
		return (NULL);
	while (minishell->input[++i])
	{
		if (minishell->input[i] == SINGLE_QUOTE)
			cut_quotes(minishell, &i, &j, SINGLE_QUOTE);
		/*{
			if (j < i)
				clean_input = ft_strjoin(clean_input,
						ft_substr(minishell->input, j, i - j));
			clean_input = ft_strjoin(clean_input,
					handle_single_quotes(minishell, ++i));
			while (minishell->input[i] && minishell->input[i] != SINGLE_QUOTE)
				i++;
			j = i + 1;
		}*/
		else if (minishell->input[i] == DOUBLE_QUOTE)
			cut_quotes(minishell, &i, &j, DOUBLE_QUOTE);
		/*{
			if (j < i)
				clean_input = ft_strjoin(clean_input,
						ft_substr(minishell->input, j, i - j));
			clean_input = ft_strjoin(clean_input,
					handle_double_quotes(minishell, ++i));
			while (minishell->input[i] && minishell->input[i] != DOUBLE_QUOTE)
				i++;
			j = i + 1;
		}*/
	}
	if (j < i)
		clean_input = ft_strjoin(clean_input, ft_substr(minishell->input, j, i
					- j));
	return (clean_input);
}
