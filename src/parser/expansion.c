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
	t_env	*current;
	char	*equal_sign;
	int		var_len;

	current = minishell->env_list;
	var_len = ft_strlen(variable);
	while (current)
	{
		if (ft_strncmp(current->env_var, variable, var_len) == 0
			&& current->env_var[var_len] == '=')
		{
			equal_sign = ft_strchr(current->env_var, '=');
			if (equal_sign)
			{
				free(variable);
				return (ft_strdup(equal_sign + 1));
			}
		}
		current = current->next;
	}
	free(variable);
	return (NULL);
}

char	*get_env_var(t_minishell *minishell, int *i, int *j)
{
	char	*clean_input;

	if (!minishell || !minishell->current_process || !i || !j)
		return (NULL);
	clean_input = NULL;
	// if (minishell->current_process[*i + 1] == '?')
	// 		return (ft_itoa(g_exit_status));
	if (*j < *i)
		clean_input = ft_strjoin_free(clean_input, ft_substr(minishell->current_process,
					*j, *i - *j));
	*j = ++(*i);
	while (minishell->current_process[*i] && ft_isalnum(minishell->current_process[*i]))
		(*i)++;
	clean_input = ft_strjoin_free(clean_input, extract_variable(minishell,
				ft_substr(minishell->current_process, *j, *i - *j)));
	*j = *i;
	return (clean_input);
}

char	*expansion(t_minishell *minishell, char *process)
{
	char	*clean_input;
	int		i;
	int		j;

	clean_input = NULL;
	i = 0;
	j = i;
	minishell->current_process = process;
	while (minishell->current_process[i])
	{
		if (minishell->current_process[i] == '$')
			clean_input = get_env_var(minishell, &i, &j);
		else
			i++;
	}
	if (j < i)
		clean_input = ft_strjoin_free(clean_input, ft_substr(minishell->current_process,
					j, i - j));
	return (clean_input);
}
