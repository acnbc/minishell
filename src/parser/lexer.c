#include "../includes/minishell.h"

// tratar outfile
static void redout_append_tokenizer( t_process *process, t_minishell *minishell, int *i)
{
    if (process->cmd_seq[*i + 1] == '>')
    {
        *i += 2;
        skip_spaces(process->cmd_seq, i);
        if (ft_strchr(process->cmd_seq, DOUBLE_QUOTE) || ft_strchr(process->cmd_seq, SINGLE_QUOTE))
            process->output_file = handle_quotes(minishell, process->cmd_seq, i);
        else
            process->output_file = get_str(process->cmd_seq, i, minishell);
        skip_spaces(process->cmd_seq, i);
        process->append_flag = 1;
        return ;
    }
    *i += 1;
    skip_spaces(process->cmd_seq, i);
    if (ft_strchr(process->cmd_seq, DOUBLE_QUOTE) || ft_strchr(process->cmd_seq, SINGLE_QUOTE))
        process->output_file = handle_quotes(minishell, process->cmd_seq, i);
    else
        process->output_file = get_str(process->cmd_seq, i, minishell);
    skip_spaces(process->cmd_seq, i);
    process->redirect_out_flag = 1;
    return ;
}

static void redin_heredoc_tokenizer( t_process *process, t_minishell *minishell, int *i)
{
    if (process->cmd_seq[*i + 1] == '<')
    {
        *i += 2;
        skip_spaces(process->cmd_seq, i);
        if (ft_strchr(process->cmd_seq, DOUBLE_QUOTE) || ft_strchr(process->cmd_seq, SINGLE_QUOTE))
            process->heredoc_delimiter = handle_quotes(minishell, process->cmd_seq, i);
        else
            process->heredoc_delimiter = get_str(process->cmd_seq, i, minishell);
        skip_spaces(process->cmd_seq, i);
        process->heredoc_flag = 1;
        return ;
    }
    *i += 1;
    skip_spaces(process->cmd_seq, i);
    if (ft_strchr(process->cmd_seq, DOUBLE_QUOTE) || ft_strchr(process->cmd_seq, SINGLE_QUOTE))
            process->input_file = handle_quotes(minishell, process->cmd_seq, i);
        else
            process->input_file = get_str(process->cmd_seq, i, minishell);
        skip_spaces(process->cmd_seq, i);
    process->redirect_in_flag = 1;
    return ;
}

int is_builtin(char *cmd)
{
    static const char   *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
    int                 i;
    
    i = -1;
    while (builtins[++i])
    {
        if (ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i])) == 0)
            return 1;
    }
    free(cmd);
    return 0;
}

static char *is_variable(char *str, t_minishell *minishell, int *i, int start)
{
	char *segment;
	char *result;

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
	return result;
}

static void word_tokenizer(t_token **tokens,  t_process *process, t_minishell *minishell, int *i)
{
    char    *cmd_seq;
    char    *segment;
    int     start;
        
    cmd_seq = process->cmd_seq;
    start = *i;
    printf("i = %d e c = %c\n", *i, cmd_seq[*i]);
    //while (cmd_seq[*i] && !ft_isspace(cmd_seq[*i]))
    while (cmd_seq[*i])
    {
        if (cmd_seq[(*i) + 1] == '>' && cmd_seq[(*i) + 1] == '<')
        {
            if (*i > start)
            {
                segment = is_variable(cmd_seq, minishell, i, start);
                if (start == 0 && is_builtin(ft_substr_safe(cmd_seq, start, *i - start, minishell)))
                    token_lstadd_back(tokens, new_token(segment, TOKEN_BUILTIN));
                else if (*i > start && start == 0)
                    token_lstadd_back(tokens, new_token(segment, TOKEN_CMD));
                else if (*i > start)
                    token_lstadd_back(tokens, new_token(segment, TOKEN_ARGS));
            }
            return ;
        }    
        else if (ft_isspace(cmd_seq[*i]))
        {    
            if (*i > start)
            {
                segment = is_variable(cmd_seq, minishell, i, start);
                if (start == 0 && is_builtin(ft_substr_safe(cmd_seq, start, *i - start, minishell)))
                    token_lstadd_back(tokens, new_token(segment, TOKEN_BUILTIN));
                else if (*i > start && start == 0)
                    token_lstadd_back(tokens, new_token(segment, TOKEN_CMD));
                else if (*i > start)
                    token_lstadd_back(tokens, new_token(segment, TOKEN_ARGS));
            }
            skip_spaces(cmd_seq, i);
            start = *i;
            continue;
        }
        else if (cmd_seq[*i] == DOUBLE_QUOTE || cmd_seq[*i] == SINGLE_QUOTE)
        {
            if (*i > start)
            {
                segment = is_variable(cmd_seq, minishell, i, start);
                token_lstadd_back(tokens, new_token(segment, TOKEN_ARGS));
            }
            token_lstadd_back(tokens, new_token(handle_quotes(minishell, cmd_seq, i), TOKEN_ARGS));
            start = *i;
        }
        else
            (*i)++;
    }
    if (*i > start)
    {
        segment = is_variable(cmd_seq, minishell, i, start);
        if (start == 0 && is_builtin(ft_substr_safe(cmd_seq, start, *i - start, minishell)))
            token_lstadd_back(tokens, new_token(segment, TOKEN_BUILTIN));
        else if (*i > start && start == 0)
            token_lstadd_back(tokens, new_token(segment, TOKEN_CMD));
        else if (*i > start)
            token_lstadd_back(tokens, new_token(segment, TOKEN_ARGS));
    }
    return ;
}

/*


static void word_tokenizer(t_token **tokens, t_process *process, t_minishell *minishell, int *i)
{
	char	*cmd_seq = process->cmd_seq;
	int		start = *i;

	while (cmd_seq[*i] && !ft_isspace(cmd_seq[*i]))
	{
		if (cmd_seq[*i] == DOUBLE_QUOTE || cmd_seq[*i] == SINGLE_QUOTE)
		{
			if (*i > start)
			{
				char *before_quote = is_variable(cmd_seq, minishell, i, start);
				token_lstadd_back(tokens, new_token(before_quote, TOKEN_ARGS));
			}
			char *quoted = handle_quotes(minishell, cmd_seq, i);
			token_lstadd_back(tokens, new_tokenecho 'literal $USER'(quoted, TOKEN_ARGS));
			start = *i;
		}
		else
			(*i)++;
	}
	if (*i > start)
	{
		char *value = is_variable(cmd_seq, minishell, i, start);
		if (start == 0 && is_builtin(value))
			token_lstadd_back(tokens, new_token(value, TOKEN_BUILTIN));
		else if (start == 0)
			token_lstadd_back(tokens, new_token(value, TOKEN_CMD));
		else
			token_lstadd_back(tokens, new_token(value, TOKEN_ARGS));
	}
}*/

void   lexer(t_minishell *minishell)
{
    t_process   *current_process;
    char        *cmd_seq;
    int         i;

    current_process = minishell->process_list;
    while (current_process)
    {
        i = -1;
        cmd_seq = current_process->cmd_seq;
        while (cmd_seq[++i])
        {
            if (cmd_seq[i] == '<' && !is_between_quotes(cmd_seq, i))
                redin_heredoc_tokenizer(current_process, minishell, &i);
            else if (cmd_seq[i] == '>' && !is_between_quotes(cmd_seq, i))
                redout_append_tokenizer(current_process, minishell, &i);
            else if (!ft_isspace(cmd_seq[i]))
                word_tokenizer(&current_process->tokens, current_process, minishell, &i);
            else
                skip_spaces(cmd_seq, &i);
        }
        current_process = current_process->next;
    }
    return ;
}

void	print_process_list(t_process *process_list)
{
    int	i;
    int	j;

    i = 0;
    printf("\n=== DEBUG: Process List ===\n");
    while (process_list != NULL)
    {
        printf("Node[%d]:\n", i++);
        printf("  cmd_seq: '%s'\n", process_list->cmd_seq);

        // Exibe arquivos de entrada, saída e delimitador de heredoc, se existirem
        if (process_list->input_file)
            printf("  input_file: '%s'\n", process_list->input_file);
        if (process_list->output_file)
            printf("  output_file: '%s'\n", process_list->output_file);
        if (process_list->heredoc_delimiter)
            printf("  heredoc_delimiter: '%s'\n", process_list->heredoc_delimiter);

        // Exibe tokens, se existirem
        t_token *tok = process_list->tokens;
        j = 0;
        while (tok)
        {
            printf("    Token[%d]: '%s' (type: %d)\n", j++, tok->value, tok->type);
            tok = tok->next;
        }

        // Exibe command, se existir
        if (process_list->command)
        {
            j = 0;
            while (process_list->command[j])
            {
                printf("    command[%d]: '%s'\n", j, process_list->command[j]);
                j++;
            }
        }
        process_list = process_list->next;
    }
    printf("=== Fim da lista de processos ===\n\n");
}
/* ---------------------------
        echo
        cd
        pwd
        export
        unset
        env
        exit
--------------------------- */