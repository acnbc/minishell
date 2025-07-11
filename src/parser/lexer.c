#include "../includes/minishell.h"

// tratar outfile
static void redout_append_tokenizer(t_process *process, int *i)
{
    if (process->cmd_seq[*i + 1] == '>')
    {
        *i += 2;
        skip_spaces(process->cmd_seq, i);
        process->output_file = get_str(process->cmd_seq, i);
        skip_spaces(process->cmd_seq, i);
        process->append_flag = 1;
        return ;
    }
    *i += 1;
    skip_spaces(process->cmd_seq, i);
    process->output_file = get_str(process->cmd_seq, i);
    skip_spaces(process->cmd_seq, i);
    process->redirect_out_flag = 1;
    return ;
}

static void redin_heredoc_tokenizer(t_process *process, int *i)
{
    if (process->cmd_seq[*i + 1] == '<')
    {
        *i += 2;
        skip_spaces(process->cmd_seq, i);
        process->heredoc_delimiter = get_str(process->cmd_seq, i);
        skip_spaces(process->cmd_seq, i);
        process->heredoc_flag = 1;
        return ;
    }
    *i += 1;
    skip_spaces(process->cmd_seq, i);
    process->input_file = get_str(process->cmd_seq, i);
    skip_spaces(process->cmd_seq, i);
    process->redirect_in_flag = 1;
    return ;
}

int is_builtin(const char *cmd)
{
    static const char   *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
    int                 i;
    
    i = -1;
    while (builtins[++i])
    {
        if (ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i])) == 0)
            return 1;
    }
    return 0;
}

// não tokenizar quando estiver entre aspas
static void word_tokenizer(t_token **tokens, t_process *process, int *i)
{
    t_token *new_node;
    int     start;

    
    start = *i;
    new_node = NULL;
    // Primeiro verificar se há áspas (ft_strchr(DOUBLE_QUOTE) || ft_strchr(SINGLE_QUOTE))
    //      se houver, remover as aspas (e expandir variáveis, se necessário) e copiar tudo para um token só
    //      se não houver, seguir o fluxo
    // Segundo verificar se há built-in (is_builtin)
    //      se houver, verificar se é a primeira palavra da string e criar um token com o nome do built-in
    //      se não for a primeira palavra, seguir o fluxo normal
    //      se não houver, seguir o fluxo
    // Terceiro criar token cmd com primeira palavra da string e criar tokens args com as demais palavras
    while (process->cmd_seq[*i] && !ft_isspace(process->cmd_seq[*i]))
        ++(*i);
    if (*i > start)
    {
        new_node = new_token(ft_substr(process->cmd_seq, start, *i - start), TOKEN_ARGS);
        //if (!new_node)
        //    safe_exit
        token_lstadd_back(tokens, new_node);
    }
    return ;
}

void   lexer(t_process *process_list)
{
    t_process   *current_process;
    char        *cmd_seq;
    int         i;

    current_process = process_list;
    while (current_process)
    {
        i = -1;
        cmd_seq = current_process->cmd_seq;
        while (cmd_seq[++i])
        {
            if (cmd_seq[i] == '<' && !is_between_quotes(cmd_seq, i))
                redin_heredoc_tokenizer(current_process, &i);
            else if (cmd_seq[i] == '>' && !is_between_quotes(cmd_seq, i))
                redout_append_tokenizer(current_process, &i);
            else if (!ft_isspace(cmd_seq[i]))
                word_tokenizer(&current_process->tokens, current_process, &i);
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