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

#include "minishell.h"

void    parser(char *input)
{
    char    **lex_ready;
    
    lex_ready = NULL;
    if (ft_strchr(input, "\""))
        lex_ready = ft_separate(handle_quotes(input, "\""));
    else if (ft_strchr(input, "\'"))
        lex_ready = ft_separate(handle_quotes(input, "\'"));
    else
        lex_ready = ft_separate(input);
    if (!lex_ready)
        return ;
    print_process_list(lex_ready);
}