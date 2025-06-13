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

char    *handle_double_quotes(char *input)
{
    
}

char	*handle_quotes(char *input, char quote)
{
	int     quotes_count;
	int     i;
	char    *clean_input;

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
        clean_input = handle_double_quotes(input);
    else
        clean_input = handle_single_quotes(input);
    return (clean_input);
}