#include "../includes/minishell.h"

void	free_process_list(t_process *process_list)
{
    t_process *tmp;

    if (!process_list)
        return ;
    while (process_list)
    {
        tmp = process_list->next;
        free(process_list->cmd_seq);
        free(process_list);
        process_list = tmp;
    }
}

void	free_env_list(t_env *env_list)
{
    t_env *tmp;

    if (!env_list)
        return ;
    while (env_list)
    {
        tmp = env_list->next;
        free(env_list->env_var);
        free(env_list);
        env_list = tmp;
    }
}

void	free_env(char **envp_copy, int i)
{
	if (!envp_copy)
        return ;
    while (--i >= 0)
		free(envp_copy[i]);
	free(envp_copy);
}