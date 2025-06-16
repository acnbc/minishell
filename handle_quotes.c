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

#include "minishell.h"

char	**expantion(char **variables, char *input)
{

}

char	**variable_expantion(char *input)
{
	int		dollar_signs;
	int		i;
	char	**variables;

	dollar_signs = 0;
	i = -1;
	while (input[++i])
	{
		if (input[i] == '$')
			dollar_signs++;
	}
	variables = (char **)safe_malloc(sizeof(char *) * dollar_signs);
	variables = expantion
}

char	*handle_double_quotes(char *input, int quotes_count)
{
	int		i;
	int		flag;
	int		clean_input_length;
	char	**expanded_variables;

	expanded_variables = NULL;
	if (ft_strchr(input, "$"))
		expanded_variables = variable_expantion(input);
	i = -2;
	flag = 1;
	while (input[++i])
	{
		if (flag == 1 || flag == quotes_count)
	}
}

char	*handle_quotes(char *input, char quote)
{
	int quotes_count;
	int i;
	char *clean_input;

	quotes_count = 0;
	i = -1;
	clean_input = NULL;
	while (input[++i])
	{
		if (input[i] == quote)
			quotes_count++;
	}
	if (quotes_count % 2 != 0)
		return (NULL);
	if (quote == '\"')
		clean_input = handle_double_quotes(input, quotes_count);
	else
		clean_input = handle_single_quotes(input, quotes_count);
	return (clean_input);
}