/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 16:39:34 by abouchat          #+#    #+#             */
/*   Updated: 2025/06/08 16:48:07 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int argc, char *argv[], char *envp[])
{
    t_minishell *minishell;

    (void)argc;
    (void)argv;
    minishell = safe_malloc(sizeof(t_minishell));
    minishell->env_list = env_list(envp);
    minishell->process_list = NULL;
	// print_env_list(minishell->env_list);
    while (1)
    {
        minishell->input = readline(MINISHELL_PROMPT);
        if (!minishell->input)
            continue;
        if (ft_strncmp(minishell->input, "exit", 5) == 0)
            safe_exit(minishell);
        if ((ft_strchr(minishell->input, DOUBLE_QUOTE)
            || ft_strchr(minishell->input, SINGLE_QUOTE))
            && !verify_quote_count(minishell->input))
        {
            free(minishell->input);
            continue ;
        }
        parser(minishell);
        free(minishell->input);
        if (minishell->process_list)
        {
            free_process_list(minishell->process_list);
            minishell->process_list = NULL;
        }
    }
    return (0);
}
