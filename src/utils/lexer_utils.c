/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:22:27 by anogueir          #+#    #+#             */
/*   Updated: 2025/07/19 16:22:30 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*void	classify_word(t_token **tokens, t_minishell *minishell, int *i, int start)
{
	char	*word;

	word = minishell->current_process;
	while (word[*i])
	{
		if ((word[*i] == '>' || word[*i] == '<') && !is_between_quotes(word,
				*i))
		{
			get_word_token(tokens, minishell, i, start);
			return ;
		}
		else if (ft_isspace(word[*i]))
		{
			if (*i > start)
				get_word_token(tokens, minishell, i, start);
			skip_spaces(word, i);
			start = *i;
			continue ;
		}
		else if (word[*i] == DOUBLE_QUOTE || word[*i] == SINGLE_QUOTE)
		{
			if (*i > start)
			{
				segment = is_variable(word, minishell, i, start);
				token_lstadd_back(tokens, new_token(segment, TOKEN_ARGS));
			}
			token_lstadd_back(tokens, new_token(handle_quotes(minishell, word,
						i), TOKEN_ARGS));
			start = *i;
		}
		else
			(*i)++;
	}
	if (*i > start)
		get_word_token(tokens, minishell, i, start);
}*/

void	get_word_token(t_token **tokens, t_minishell *minishell, int *i,
		int start)
{
	char	*cmd_seq;
	char	*segment;

	cmd_seq = minishell->current_process;
	segment = is_variable(cmd_seq, minishell, i, start);
	if (start == 0 && is_builtin(ft_substr_safe(cmd_seq, start, *i - start,
				minishell)))
		token_lstadd_back(tokens, new_token(segment, TOKEN_BUILTIN));
	else if (*i > start && start == 0)
		token_lstadd_back(tokens, new_token(segment, TOKEN_CMD));
	else if (*i > start)
		token_lstadd_back(tokens, new_token(segment, TOKEN_ARGS));
}

int	is_builtin(char *cmd)
{
	static const char	*builtins[] = {"echo", "cd", "pwd", "export", "unset",
			"env", "exit", NULL};
	int					i;

	i = -1;
	while (builtins[++i])
	{
		if (ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i])) == 0)
			return (1);
	}
	free(cmd);
	return (0);
}

char	*is_variable(char *str, t_minishell *minishell, int *i, int start)
{
	char	*segment;
	char	*result;

	segment = ft_substr_safe(str, start, *i - start, minishell);
	if (!segment)
		return (NULL);
	if (ft_strchr(segment, '$'))
	{
		result = expansion(minishell, segment);
		free(segment);
		if (!result)
			return (NULL);
	}
	else
		result = segment;
	return (result);
}

void	tokenize(char *cmd_seq, t_process *current_process,
		t_minishell *minishell)
{
	int	i;

	i = 0;
	while (cmd_seq[i])
	{
		if (cmd_seq[i] == '<' && !is_between_quotes(cmd_seq, i))
		{
			redin_heredoc_tokenizer(current_process, minishell, &i);
			continue ;
		}
		else if (cmd_seq[i] == '>' && !is_between_quotes(cmd_seq, i))
		{
			redout_append_tokenizer(current_process, minishell, &i);
			continue ;
		}
		else if (!ft_isspace(cmd_seq[i]))
		{
			word_tokenizer(&current_process->tokens, current_process, minishell,
				&i);
			continue ;
		}
		else
			skip_spaces(cmd_seq, &i);
	}
}

void	print_process_list(t_process *process_list)
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
		// Redirecionamentos
		if (process_list->input_file)
			printf("  input_file:         '%s'\n", process_list->input_file);
		if (process_list->output_file)
			printf("  output_file:        '%s'\n", process_list->output_file);
		if (process_list->heredoc_delimiter)
			printf("  heredoc_delimiter:  '%s'\n",
				process_list->heredoc_delimiter);
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
		// Command array
		if (process_list->command)
		{
			j = 0;
			while (process_list->command[j])
			{
				printf("    command[%d]:       '%s'\n", j,
					process_list->command[j]);
				j++;
			}
		}
		// Args array
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
}
