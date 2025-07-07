/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 12:45:20 by anogueir          #+#    #+#             */
/*   Updated: 2025/07/03 12:45:22 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_whitespace(char *input, int i)
{
	while (input[i] && ft_isspace(input[i]))
		i++;
	return (i);
}

void	get_cmd_seq(t_process **phrases, char *input, int i, int j)
{
	char	*phrase;
	char	*temp;

	phrase = NULL;
	temp = NULL;
	temp = ft_substr(input, j, i - j);
	phrase = ft_strtrim(temp, " \t");
	free(temp);
	if (phrase && *phrase)
		add_process(phrases, new_process(phrase));
	else
		free(phrase);
}

static int	get_operator(t_process **phrases, char *input, int i)
{
	if ((input[i] == '<' && input[i + 1] == '<') || (input[i] == '>' && input[i
			+ 1] == '>'))
	{
		add_process(phrases, new_process(ft_substr(input, i, 2)));
		i += 2;
	}
	else
	{
		add_process(phrases, new_process(ft_substr(input, i, 1)));
		i += 1;
	}
	return (i);
}

t_process	*separate_process(char *input)
{
	int			i;
	int			j;
	int		double_quote_flag;
	static char	separators[] = "<>|";
	t_process	*phrases;

	if (!input)
		return (NULL);
	phrases = NULL;
	i = skip_whitespace(input, 0);
	j = i;
	double_quote_flag = 0;
	while (input[i])
	{
		if (input[i] == DOUBLE_QUOTE)
		{
			if (double_quote_flag == 0)
				double_quote_flag = 1;
			else
				double_quote_flag = 0;
			//i++;
		}
		if (ft_strchr(separators, input[i]) && double_quote_flag == 0)
		{
			if (i > j)
				get_cmd_seq(&phrases, input, i, j);
			i = get_operator(&phrases, input, i);
			j = skip_whitespace(input, i);
		}
		else
			i++;
	}
	if (i > j)
		get_cmd_seq(&phrases, input, i, j);
	return (phrases);
}
