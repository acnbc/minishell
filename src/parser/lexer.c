#include "../includes/minishell.h"

/*t_token *tokenizer(t_process *process)
{
    TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND
}*/

void    word_tokenizer(t_token **tokens, char *cmd_seq, int *i)
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
            if (is_stopchar(current_process->cmd_seq[i]))
                word_tokenizer(&tokens, current_process->cmd_seq, &i);
        }
        current_process = current_process->next;
    }
}