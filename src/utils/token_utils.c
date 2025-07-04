#include "../includes/minishell.h"
// token_new.c para criar um novo nó de token
// token_tokensadd_back.c para adicionar um nó de token ao final da lista
// free_token_list.c para liberar a lista de tokens
// tokenizer.c para criar uma lista de tokens a partir de uma string vinda do nó 
// de processo da lista de processos

t_token    *new_token(char *value, enum e_token_type type)
{
    t_token	*new;

    new = safe_malloc(sizeof(t_token));
    new->value = value;
    new->type = type;
    new->next = NULL;
    return (new);
}

void    token_lstadd_back(t_token **tokens, t_token *new)
{
    t_token	*curr;

    if (!tokens || !new)
        return ;
    if (!*tokens)
        *tokens = new;
    else
    {
        curr = *tokens;
        while (curr->next)
            curr = curr->next;
        curr->next = new;
    }
}