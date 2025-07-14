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

void	parser(t_minishell *minishell)
{
    //t_process	*current;
    //char		*tmp;

    minishell->process_list = separate_process(minishell->input);
	if (!minishell->process_list)
		return ;
    lexer(minishell);
	// parsing(minishell->process_list);
    /*while (current)
    {
        if (ft_strchr(current->cmd_seq, DOUBLE_QUOTE) || ft_strchr(current->cmd_seq, SINGLE_QUOTE))
        {
            tmp = handle_quotes(minishell, current->cmd_seq);
            free(current->cmd_seq);
            current->cmd_seq = tmp;
        }
        else if (ft_strchr(current->cmd_seq, '$'))
        {
            tmp = expansion(minishell, current->cmd_seq);
            free(current->cmd_seq);
            current->cmd_seq = tmp;
        }
		// free (current->cmd_seq);
		// current->args = ft_split(tmp, ' ');
        current = current->next;
    }*/
    print_process_list(minishell->process_list);
}
