/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 21:15:13 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/14 21:19:04 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int mini_shell(t_minishell *minishell)
{
    if (!minishell)
        return (0);
    minishell->input = readline(MINISHELL_PROMPT);
    if (!minishell->input)
        return (0);
    if (ft_strncmp(minishell->input, "exit", 5) == 0)
        safe_exit(minishell);
    if ((ft_strchr(minishell->input, DOUBLE_QUOTE)
            || ft_strchr(minishell->input, SINGLE_QUOTE))
        && !verify_quote_count(minishell->input))
    {
        free(minishell->input);
        return (1);
    }
    if (!parser(minishell))
    {
        flush(minishell);
        return (0);
    }
    executor(minishell);
    return (1);    
}