/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:15:13 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/31 15:11:47 by codespace        ###   ########.fr       */
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
	if (mini->input[0] == '$')
	{
		expand_env_vars(mini);
		return (0);
	}
	if (ft_strstr(mini->input, "exit"))
		ft_exit(mini);
	if (ft_strncmp(".", mini->input, 2) == 0)
	{
		ft_printf("filename argument required\n");
		ft_printf(".: usage: . filename [arguments]\n");
		return (0);
	}
	if (ft_strncmp("..", mini->input, 2) == 0)
	{
		ft_printf("..: command not found\n");
		return (0);
	}
	if ((ft_strchr(mini->input, DOUBLE_QUOTE)
			|| ft_strchr(mini->input, SINGLE_QUOTE))
		&& !verify_quote_count(mini->input))
		return (0);
	return (1);
}

void	mini_shell(t_minishell *mini)
{
	char	*input;

	input = readline(MINISHELL_PROMPT);
	mini->input = ft_strtrim(input, " \t\n\v\f\r");
	if (!mini->input || mini->input[0] == '\0')
	{
		free(input);
		free(mini->input);
		mini->input = NULL;
		return ;
	}
	free(input);
	if (!mini->input)
		mini->input = ft_strdup("exit");
	add_history(mini->input);
	if (!first_input_checks(mini))
		return ;
	if (!parser(mini))
		return ;
	executor(mini);
	return ;
}
