/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_separate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:03:47 by anogueir          #+#    #+#             */
/*   Updated: 2025/06/12 12:03:49 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_isspace(char c)
{
    return (c == ' ' || (c >= '\t' && c <= '\r'));
}

int skip_whitespace(char *input, int i)
{
    while (input[i] && ft_isspace(input[i]))
        i++;
    return (i);
}

void    get_cmd_seq(t_process **phrases, char *input, int i, int j)
{
    char        *phrase;
    
    phrase = NULL;
    phrase = ft_strtrim(ft_substr(input, j, i - j), " \t");
    if (phrase && *phrase)
        add_process(phrases, new_process(phrase));
    else
        free(phrase);
}

int    get_operator(t_process **phrases, char *input, int i)
{
    if ((input[i] == '<' && input[i + 1] == '<') || 
        (input[i] == '>' && input[i + 1] == '>'))
    {
        add_process(phrases, new_process(ft_substr(input, i, 2)));
        i += 2;
    }
    else
    {
        add_process(phrases, new_process(ft_substr(input, i, 1)));
        i += 1;
    }
    return (i);
}

t_process   *ft_separate(char *input)
{
    int i;
    int j;
    static char separators[] = "<>|";
    t_process   *phrases;
    
    phrases = NULL;
    i = 0;
    i = skip_whitespace(input, i);
    j = i;    
    while (input[i])
    {
        if (ft_strchr(separators, input[i]))
        {
            if (i > j)
                get_cmd_seq(&phrases, input, i, j);
            i = get_operator(&phrases, input, i);
            i = skip_whitespace(input, i);
            j = i;
        }
        else
            i++;
    }
    if (i > j)
        get_cmd_seq(&phrases, input, i, j);
    return (phrases);
}

void print_process_list(t_process *process_list)
{
    int i = 0;
    
    printf("\n=== DEBUG: Process List ===\n");
    while (process_list != NULL)
    {
        printf("Node[%d]: '%s'\n", i++, process_list->cmd_seq);
        process_list = process_list->next;
    }
    printf("=== Total: %d nodes ===\n\n", i);
}