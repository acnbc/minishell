/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:15:13 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/24 16:38:18 by abouchat         ###   ########.fr       */
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

int	mini_shell(t_minishell *mini)
{
	if (!mini)
		return (0);
	mini->input = readline(MINISHELL_PROMPT);
	if (!mini->input)
		mini->input = ft_strdup("exit");
	if (first_input_checks(mini))
		return (1);
	if (!parser(mini))
		return (1);
	executor(mini);
	unlink_heredoc_files(mini);
	add_history(mini->input);
	return (1);
}
