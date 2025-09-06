/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:15:13 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/04 08:32:20 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		if (str[i] == to_find[j])
		{
			while ((to_find[j] != '\0') && (str[i + j] == to_find[j]))
				j++;
			if (to_find[j] == '\0')
				return (&str[i]);
		}
		i++;
	}
	return (NULL);
}

static int	check_dot_arg(t_minishell *mini)
{
	if (ft_strncmp(".", mini->input, 2) == 0)
	{
		ft_printf("filename argument required\n");
		ft_printf(".: usage: . filename [arguments]\n");
		g_exit_status = 2;
		return (0);
	}
	if (ft_strncmp("..", mini->input, 2) == 0)
	{
		ft_printf("..: command not found\n");
		g_exit_status = 127;
		return (0);
	}
	return (1);
}

static int	first_input_checks(t_minishell *mini)
{
	if (mini->input[0] == '$')
	{
		expand_env_vars(mini);
		return (0);
	}
	if (!check_dot_arg(mini))
		return (0);
	if ((ft_strchr(mini->input, DOUBLE_QUOTE)
			|| ft_strchr(mini->input, SINGLE_QUOTE))
		&& verify_quote_count(mini->input))
		return (0);
	return (1);
}

void	mini_shell(t_minishell *mini)
{
	mini->input = readline(MINISHELL_PROMPT);
	if (!mini->input)
		mini->input = ft_strdup("exit");
	if (!mini->input || mini->input[0] == '\0')
	{
		free(mini->input);
		mini->input = NULL;
		return ;
	}
	//mini->input = ft_strtrim(input, " \t\n\v\f\r");
	add_history(mini->input);
	if (!first_input_checks(mini))
		return ;
	if (!parser(mini))
		return ;
	executor(mini);
	return ;
}
