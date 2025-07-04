#include "../includes/minishell.h"

static void    redout_append_tokenizer(t_token **tokens, char *cmd_seq, int *i)
{
    t_token *new_node;

    if (cmd_seq[*i + 1] == '>')
    {
        new_node = new_token(ft_substr(cmd_seq, *i, 2), TOKEN_APPEND);
        if (!new_node)
        //    safe_exit
        token_lstaddbak(tokens, new_node);
        *i += 2;
        return ;
    }
    new_node = new_token(ft_substr(cmd_seq, *i, 1), TOKEN_REDIRECT_OUT);
    if (!new_node)
    //    safe_exit
    token_lstaddbak(tokens, new_node);
    ++(*i);
}

static void    redin_heredoc_tokenizer(t_token **tokens, char *cmd_seq, int *i)
{
    t_token *new_node;

    if (cmd_seq[*i + 1] == '<')
    {
        new_node = new_token(ft_substr(cmd_seq, *i, 2), TOKEN_HEREDOC);
        if (!new_node)
        //    safe_exit
        token_lstaddbak(tokens, new_node);
        *i += 2;
        return ;
    }
    new_node = new_token(ft_substr(cmd_seq, *i, 1), TOKEN_REDIRECT_IN);
    if (!new_node)
    //    safe_exit
    token_lstaddbak(tokens, new_node);
    ++(*i);
}

static void    pipe_tokenizer(t_token **tokens, char *cmd_seq, int *i)
{
    t_token *new_node;

    new_node = new_token(ft_substr(cmd_seq, *i, 1), TOKEN_PIPE);
    if (!new_node)
    //    safe_exit
    token_lstaddbak(tokens, new_node);
    ++(*i);
}

static void    word_tokenizer(t_token **tokens, char *cmd_seq, int *i)
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
        if (!new_node)
        //    safe_exit
        token_lstaddbak(tokens, new_node);
    }
    return ;
}

t_token *lexer(t_process *process_list)
{
    t_token     *tokens;
    t_process   *current_process;
    int         i;

    tokens = NULL;
    current_process = process_list;
    while (current_process)
    {
        i = -1;
        while (current_process->cmd_seq[++i])
        {
            if (current_process->cmd_seq[i] == '|' && i == 0)
                pipe_tokenizer(&tokens, current_process->cmd_seq, &i);
            else if (current_process->cmd_seq[i] == '<' && i == 0)
                redin_heredoc_tokenizer(&tokens, current_process->cmd_seq, &i);
            else if (current_process->cmd_seq[i] == '>' && i == 0)
                redout_append_tokenizer(&tokens, current_process->cmd_seq, &i);
            else
                word_tokenizer(&tokens, current_process->cmd_seq, &i);
        }
        current_process = current_process->next;
    }
    return (tokens);
}