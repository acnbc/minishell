/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:23:12 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/15 09:10:10 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



static char	*get_redir_target(t_minishell *mini, int *i)
{
	char	*cmd_seq;
	char	*temp;

	cmd_seq = mini->cur_proc->cmd_seq;
	skip_spaces(cmd_seq, i);
	if (cmd_seq[*i] == DOUBLE_QUOTE || cmd_seq[*i] == SINGLE_QUOTE)
	{
		temp = handle_quotes(mini, cmd_seq, i);
		mini->cur_proc->heredoc_quote_flag = 1;
	}
	else
		temp = get_str(cmd_seq, i, mini);
	skip_spaces(cmd_seq, i);
	if (temp && (ft_strchr(temp, '<') || ft_strchr(temp, '>')))
	{
		free(temp);
		temp = NULL;
	}
	return (temp);
}

static void	assign_file(char **file, t_minishell *mini, int *i)
{
	if (*file)
		free(*file);
	*file = get_redir_target(mini, i);
}

int	redout_append_tokenizer(t_minishell *mini, int *i)
{
	char	*cmd_seq;

	cmd_seq = mini->cur_proc->cmd_seq;
	// corrigir >>>
	if (cmd_seq[*i + 1] && cmd_seq[*i + 1] == '>'
		&& cmd_seq[*i + 2] && cmd_seq[*i + 2] == '>')
		return (0);
	if (cmd_seq[*i + 1] && cmd_seq[*i + 1] == '>')
	{
		*i += 2;
		mini->cur_proc->append_flag = 1;
	}
	else
	{
		*i += 1;
		mini->cur_proc->redirect_out_flag = 1;
	}
	assign_file(&mini->cur_proc->output_file, mini, i);
	return (1);
}

int	redin_heredoc_tokenizer(t_minishell *mini, int *i)
{
	char	*cmd_seq;

	cmd_seq = mini->cur_proc->cmd_seq;
	// corrigir <<<
	if (cmd_seq[*i + 1] && cmd_seq[*i + 1] == '<'
		&& cmd_seq[*i + 2] && cmd_seq[*i + 2] == '<')
		return (0);
	if (cmd_seq[*i + 1] && cmd_seq[*i + 1] == '<')
	{
		*i += 2;
		mini->cur_proc->heredoc_flag = 1;
	}
	else
	{
		*i += 1;
		mini->cur_proc->redirect_in_flag = 1;
	}
	if (mini->cur_proc->heredoc_flag)
		assign_file(&mini->cur_proc->delimiter, mini, i);
	else
		assign_file(&mini->cur_proc->input_file, mini, i);
	return (1);
}

int	lexer(t_minishell *mini)
{
	t_process	*cur_proc;

	cur_proc = mini->process_list;
	while (cur_proc)
	{
		mini->cur_proc = cur_proc;
		if (!tokenize(mini))
			return (0);
		cur_proc = cur_proc->next;
	}
	return (1);
}

/*1. get_redir_target

    Função: Extrai o alvo (nome do arquivo ou delimitador) de uma operação de redirecionamento no comando.
    Como funciona:
        Pula espaços.
        Se o próximo caractere for aspas, chama handle_quotes para pegar o conteúdo entre aspas.
        Caso contrário, chama get_str para pegar a próxima palavra.
        Se o resultado contiver < ou >, libera e retorna NULL (evita nomes inválidos).
        Retorna o nome do arquivo ou delimitador.
2. assign_file

    Função: Atribui o nome do arquivo ou delimitador ao ponteiro passado.
    Como funciona:
        Libera o valor anterior do ponteiro, se existir.
        Chama get_redir_target para obter o novo valor e atribui ao ponteiro.

3. redout_append_tokenizer

    Função: Processa o token de redirecionamento de saída (> ou >>) no comando.
    Como funciona:
        Se encontrar >>, ajusta o índice e seta a flag de append.
        Se encontrar apenas >, ajusta o índice e seta a flag de redirecionamento de saída.
        Chama assign_file para definir o arquivo de saída.
4. redin_heredoc_tokenizer

    Função: Processa o token de redirecionamento de entrada (< ou <<) no comando.
    Como funciona:
        Se encontrar <<, ajusta o índice e seta a flag de heredoc.
        Se encontrar apenas <, ajusta o índice e seta a flag de redirecionamento de entrada.
        Chama assign_file para definir o arquivo de entrada ou o delimitador do heredoc.

5. lexer

    Função: Realiza a análise léxica (tokenização) dos comandos de todos os processos.
    Como funciona:
        Percorre a lista de processos.
        Para cada processo, chama tokenize para identificar e separar os tokens do comando.
*/