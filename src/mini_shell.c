/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:15:13 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/29 09:14:07 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_exit(t_minishell *mini)
{
	char			*input;

	input = ft_strtrim(mini->input, " \t\n\v\f\r");
	if (ft_strncmp(input, "exit", 4) == 0 && (input[4] == '\0'
			|| ft_isspace(input[4])))
	{
		write(1, "exit\n", 5);
		free(input);
		safe_exit(mini);
	}
	return ;
}

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

static int	first_input_checks(t_minishell *mini)
{
	if (ft_strstr(mini->input, "exit"))
		ft_exit(mini);
	if (ft_strncmp(".", mini->input, 2) == 0)
	{
		ft_printf("filename argument required\n");
		ft_printf(".: usage: . filename [arguments]\n");
		return (1);
	}
	if (ft_strncmp("..", mini->input, 2) == 0)
	{
		ft_printf("..: command not found\n");
		return (1);
	}
	if ((ft_strchr(mini->input, DOUBLE_QUOTE)
			|| ft_strchr(mini->input, SINGLE_QUOTE))
		&& !verify_quote_count(mini->input))
		return (1);
	return (0);
}

void	mini_shell(t_minishell *mini)
{
	mini->input = readline(MINISHELL_PROMPT);
	if (!mini->input)
		mini->input = ft_strdup("exit");
	add_history(mini->input);
	if (first_input_checks(mini))
		return ;
	if (!parser(mini))
		return ;
	executor(mini);
	return ;
}
