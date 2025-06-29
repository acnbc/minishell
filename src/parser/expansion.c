/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:01:02 by anogueir          #+#    #+#             */
/*   Updated: 2025/06/17 12:01:04 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_stopchar(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*extract_variable(t_minishell *minishell, char *variable)
{
	char	*equal_sign;
	int		i;
	int		var_len;

	equal_sign = NULL;
	var_len = ft_strlen(variable);
	i = -1;
	while (minishell->envp_copy[++i])
	{
		if (ft_strncmp(minishell->envp_copy[i], variable, var_len) == 0)
		{
			equal_sign = ft_strchr(minishell->envp_copy[i], '=');
			if (equal_sign)
			{
				free(variable);
				return (ft_strdup(equal_sign + 1));
			}
		}
	}
	free(variable);
	return (NULL);
}

char	*expansion(t_minishell *minishell)
{
	char	*clean_input;
	int		i;
	int		j;
	
	clean_input = NULL;
	i = 0;
	j = i;
	while (minishell->input[i])
	{
		if (minishell->input[i] == '$')
		{
			if (j < i)
				clean_input = ft_strjoin(clean_input, ft_substr(minishell->input, j, i - j));
			j = ++i;
			while (minishell->input[i] && ft_isalnum(minishell->input[i]))
				i++;
			clean_input = ft_strjoin(clean_input, extract_variable(minishell, ft_substr(minishell->input, j, i - j)));
			j = i;
		}
		else
			i++;
	}
	if (j < i)
        clean_input = ft_strjoin(clean_input, ft_substr(minishell->input, j, i - j));
    return (clean_input);
}