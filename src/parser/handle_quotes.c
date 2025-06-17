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

char	*handle_double_quotes(t_minishell *minishell, int quotes_count)
{
	int		i;
	int		flag;
	int		clean_input_length;
	char	**expanded_variables;

	expanded_variables = NULL;
	if (ft_strchr(minishell->input, "$"))
		expanded_variables = variable_expansion(minishell);
	i = -2;
	flag = 1;
	while (minishell->input[++i])
	{
		if (flag == 1 || flag == quotes_count)
	}
}

char	*handle_quotes(t_minishell *minishell, t_quote quote)
{
	int quotes_count;
	int i;
	char *clean_input;

	quotes_count = 0;
	i = -1;
	clean_input = NULL;
	while (minishell->input[++i])
	{
		if (minishell->input[i] == quote)
			quotes_count++;
	}
	if (quotes_count % 2 != 0)
		return (NULL);
	if (quote == DOUBLE_QUOTE)
		clean_input = handle_double_quotes(minishell, quotes_count);
	else
		clean_input = handle_single_quotes(minishell, quotes_count);
	return (clean_input);
}