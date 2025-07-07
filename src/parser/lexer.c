#include "../includes/minishell.h"

// tratar outfile
static void redout_append_tokenizer(t_token **tokens, char *cmd_seq, int *i)
{
    t_token *new_node;

    if (cmd_seq[*i + 1] == '>')
    {
        new_node = new_token(ft_substr(cmd_seq, *i, 2), TOKEN_APPEND);
        //if (!new_node)
        //    safe_exit
        token_lstadd_back(tokens, new_node);
        ++(*i);
        return ;
    }
    new_node = new_token(ft_substr(cmd_seq, *i, 1), TOKEN_REDIRECT_OUT);
    //if (!new_node)
    //    safe_exit
    token_lstadd_back(tokens, new_node);
    return ;
}

// Tratar infile e heredoc delimiter
static void redin_heredoc_tokenizer(t_token **tokens, char *cmd_seq, int *i)
{
    t_token *new_node;

    if (cmd_seq[*i + 1] == '<')
    {
        new_node = new_token(ft_substr(cmd_seq, *i, 2), TOKEN_HEREDOC);
        //if (!new_node)
        //    safe_exit
        token_lstadd_back(tokens, new_node);
        ++(*i);
        return ;
    }
    new_node = new_token(ft_substr(cmd_seq, *i, 1), TOKEN_REDIRECT_IN);
    //if (!new_node)
    //    safe_exit
    token_lstadd_back(tokens, new_node);
    return ;
}

static void pipe_tokenizer(t_token **tokens, char *cmd_seq, int *i)
{
    t_token *new_node;

    new_node = new_token(ft_substr(cmd_seq, *i, 1), TOKEN_PIPE);
    //if (!new_node)
    //    safe_exit
    token_lstadd_back(tokens, new_node);
    return ;
}

static void word_tokenizer(t_token **tokens, char *cmd_seq, int *i)
{
    t_token *new_node;
    int     start;

    start = *i;
    new_node = NULL;
    while (cmd_seq[*i] && !ft_isspace(cmd_seq[*i]))
        ++(*i);
    if (*i > start)
    {
        new_node = new_token(ft_substr(cmd_seq, start, *i - start), TOKEN_WORD);
        //if (!new_node)
        //    safe_exit
        token_lstadd_back(tokens, new_node);
    }
    return ;
}

t_process   *lexer(t_process *process_list)
{
    t_process   *current_process;
    int         i;

    current_process = process_list;
    while (current_process)
    {
        i = -1;
        while (current_process->cmd_seq[++i])
        {
            if (current_process->cmd_seq[i] == '|')
                pipe_tokenizer(&current_process->tokens, current_process->cmd_seq, &i);
            else if (current_process->cmd_seq[i] == '<')
                redin_heredoc_tokenizer(&current_process->tokens, current_process->cmd_seq, &i);
            else if (current_process->cmd_seq[i] == '>')
                redout_append_tokenizer(&current_process->tokens, current_process->cmd_seq, &i);
            else
                word_tokenizer(&current_process->tokens, current_process->cmd_seq, &i);
        }
        current_process = current_process->next;
    }
    return (process_list);
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