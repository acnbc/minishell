#include "minishell.h"

char    **ft_separate(char *input)
{
    int i;
    int j;
    int k;
    static char separators[] = "<>|";
    char        **phrases = malloc(sizeof(char *) * 20);
    
    i = 0;
    j = 0;
    k = 0;
    
    while (input[i])
    {
        if (ft_strchr(separators, input[i]))
        {
            // Aloca e copia a parte antes do separador
            if (i > j)
            {
                phrases[k] = malloc(i - j + 1);
                ft_strlcpy(phrases[k++], input + j, i - j + 1);
            }
            
            // Trata separadores de 2 caracteres (<< ou >>)
            if ((input[i] == '<' && input[i+1] == '<') || 
                (input[i] == '>' && input[i+1] == '>'))
            {
                phrases[k] = malloc(3);
                ft_strlcpy(phrases[k++], input + i, 3);
                i += 2;
                j = i;
            }
            else // Separador de 1 caractere
            {
                phrases[k] = malloc(2);
                ft_strlcpy(phrases[k++], input + i, 2);
                i += 1;
                j = i;
            }
        }
        else
        {
            i++;
        }
    }
    
    // Copia o restante após o último separador
    if (i > j) {
        phrases[k] = malloc(i - j + 1);
        ft_strlcpy(phrases[k++], input + j, i - j + 1);
    }
    
    phrases[k] = NULL; // Termina o array com NULL
    
    // Debug: imprime todas as frases
    for (i = 0; i < k; i++)
        printf("Phrase %d: '%s'\n", i, phrases[i]);
    
    return (phrases);
}