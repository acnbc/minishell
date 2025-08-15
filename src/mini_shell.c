/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:15:13 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/15 09:06:54 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	mini_shell(t_minishell *mini)
{
	if (!mini)
		return (0);
	mini->input = readline(MINISHELL_PROMPT);
	if (!mini->input)
		return (0);
	if (ft_strncmp(mini->input, "exit", 5) == 0)
		safe_exit(mini);
	if ((ft_strchr(mini->input, DOUBLE_QUOTE)
			|| ft_strchr(mini->input, SINGLE_QUOTE))
		&& !verify_quote_count(mini->input))
	{
		free(mini->input);
		return (1);
	}
	if (!parser(mini))
	{
		flush(mini);
		return (0);
	}
	executor(mini);
	return (1);
}
