/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:37:33 by anogueir          #+#    #+#             */
/*   Updated: 2025/06/12 19:37:34 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    parser(t_minishell *minishell)
{
    char    **lex_ready;
    
    lex_ready = NULL;
    if (ft_strchr(minishell->input, DOUBLE_QUOTE))
        lex_ready = ft_separate(handle_quotes(minishell, DOUBLE_QUOTE));
    else if (ft_strchr(input, SINGLE_QUOTE))
        lex_ready = ft_separate(handle_quotes(minishell, SINGLE_QUOTE));
    else
        lex_ready = ft_separate(minishell->input);
    if (!lex_ready)
        return ;
    print_process_list(lex_ready);
}