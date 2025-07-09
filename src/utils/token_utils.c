#include "../includes/minishell.h"

t_token    *new_token(char *value, enum e_token_type type)
{
    t_token	*new;

    if (*value == '\0')
        return (NULL);
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