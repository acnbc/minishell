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

/*void	parser(t_minishell *minishell)
{
	char		*processed_input;
	t_process	*lexer_ready;

	if (!minishell || !minishell->input)
		return ;
	lexer_ready = NULL;
	if (ft_strchr(minishell->input, DOUBLE_QUOTE) || ft_strchr(minishell->input,
			SINGLE_QUOTE))
		processed_input = handle_quotes(minishell);
	else if (ft_strchr(minishell->input, '$'))
		processed_input = expansion(minishell);
	else
		processed_input = minishell->input;
	if (processed_input)
	{
		lexer_ready = separate_process(processed_input);
		if (processed_input != minishell->input)
			free(processed_input);
	}
	if (lexer_ready)
	{
		if (minishell->process_list)
			free_process_list(minishell->process_list);
		minishell->process_list = lexer_ready;
		print_process_list(lexer_ready);
	}
}*/

// ...existing code...

void	parser(t_minishell *minishell)
{
    t_process	*current;
    char		*tmp;

    minishell->process_list = separate_process(minishell->input);
	if (!minishell->process_list)
		return ;
    current = minishell->process_list;
    while (current)
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
        current = current->next;
    }
    print_process_list(minishell->process_list);
}


//	em handle_quotes.c:
//		retirar a expansão de variável de cut_double_quote
//		alterar cut_double_quote para remover aspas duplas da mesma forma que cut_single_quote remove aspas simples
//	em parser.c
//		separar processos com separate_process
//		fazer a expansão de processo em processo
//		remover aspas de processo em processo
// 
