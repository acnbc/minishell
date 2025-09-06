/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 20:34:22 by anogueir          #+#    #+#             */
/*   Updated: 2025/09/06 11:34:51 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	process_redirection(t_minishell *mini, int *i)
{
	int	redir_result;

	redir_result = handle_redirection(mini, i);
	if (redir_result == 1)
		return (1);
	else if (redir_result == -1)
		return (-1);
	return (0);
}

int	process_word_or_space(t_minishell *mini, int *i)
{
	char	*cmd_seq;

	cmd_seq = mini->cur_proc->cmd_seq;
	if (!ft_isspace(cmd_seq[*i]))
	{
		word_tokenizer(mini, i);
		return (1);
	}
	else
	{
		skip_spaces(cmd_seq, i);
		return (1);
	}
}

int	validate_redirects(t_minishell *mini)
{
	if (mini->cur_proc->redirect_in_flag && !mini->cur_proc->input_file)
		return (0);
	if (mini->cur_proc->redirect_out_flag && !mini->cur_proc->output_file)
		return (0);
	if (mini->cur_proc->heredoc_flag && !mini->cur_proc->delimiter)
		return (0);
	return (1);
}

/*void	print_process_list(t_process *process_list)
{
	int		i;
	int		j;
	t_token	*tok;

	i = 0;
	printf("\n=== DEBUG: Process List ===\n");
	while (process_list != NULL)
	{
		printf("Node[%d]:\n", i++);
		printf("  cmd_seq:            '%s'\n", process_list->cmd_seq);
		// Caminho resolvido para o comando
		if (process_list->path)
			printf("  path:               '%s'\n", process_list->path);
		// Redirecionamentos
		if (process_list->input_file)
			printf("  input_file:         '%s'\n", process_list->input_file);
		if (process_list->output_file)
			printf("  output_file:        '%s'\n", process_list->output_file);
		if (process_list->delimiter)
			printf("  delimiter:  '%s'\n",
				process_list->delimiter);
		// Flags
		printf("  append_flag:        %d\n", process_list->append_flag);
		printf("  redirect_in_flag:   %d\n", process_list->redirect_in_flag);
		printf("  redirect_out_flag:  %d\n", process_list->redirect_out_flag);
		printf("  heredoc_flag:       %d\n", process_list->heredoc_flag);
		printf("  double_quote_flag:  %d\n", process_list->double_quote_flag);
		printf("  single_quote_flag:  %d\n", process_list->single_quote_flag);
		// Tokens
		tok = process_list->tokens;
		j = 0;
		while (tok)
		{
			printf("    Token[%d]:         '%s' (type: %d)\n", j++, tok->value,
				tok->type);
			tok = tok->next;
		}
		if (process_list->args)
		{
			j = 0;
			while (process_list->args[j])
			{
				printf("    args[%d]:          '%s'\n", j,
					process_list->args[j]);
				j++;
			}
		}
		process_list = process_list->next;
	}
	printf("=== Fim da lista de processos ===\n\n");
}*/
