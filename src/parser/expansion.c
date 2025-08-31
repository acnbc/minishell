/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:01:02 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/31 12:44:59 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_stopchar(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*extract_variable(t_minishell *mini, char *variable)
{
	t_env	*current;
	int		var_len;

	if (variable[0] == '?' && !is_stopchar(variable[1]))
	{
		free(variable);
		return (ft_itoa(g_exit_status));
	}
	current = mini->env_list;
	var_len = ft_strlen(variable);
	while (current)
	{
		if (ft_strncmp(current->var_name, variable, var_len) == 0
			&& (int) ft_strlen(current->var_name) == var_len)
		{
			free(variable);
			return (ft_strdup(current->var_cont));
		}
		current = current->next;
	}
	free(variable);
	return (NULL);
}

char	*get_env_var(t_minishell *mini, char *segment, int *i, int *j)
{
	char	*clean_input;

	clean_input = NULL;
	if (*j < *i)
		clean_input = strjoin_free(clean_input, ft_substr(segment, *j, *i
					- *j));
	*j = ++(*i);
	if (segment[*i] == '?')
	{
		(*i)++;
		clean_input = strjoin_free(clean_input, extract_variable(mini,
					ft_strdup("?")));
		*j = *i;
		return (clean_input);
	}
	while (segment[*i] && is_stopchar(segment[*i]))
		(*i)++;
	clean_input = strjoin_free(clean_input, extract_variable(mini,
				ft_substr(segment, *j, *i - *j)));
	*j = *i;
	return (clean_input);
}

char	*expansion(t_minishell *mini, char *segment)
{
	char	*clean_input;
	int		i;
	int		j;

	clean_input = NULL;
	i = 0;
	j = i;
	while (segment[i])
	{
		if (segment[i] == '$' && segment[i + 1] != '\0'
			&& (is_stopchar(segment[i + 1]) || segment[i + 1] == '?'))
			clean_input = get_env_var(mini, segment, &i, &j);
		else
			i++;
	}
	if (j < i)
		clean_input = strjoin_free(clean_input, ft_substr(segment, j, i
					- j));
	return (clean_input);
}
