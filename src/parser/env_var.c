/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 13:49:59 by codespace         #+#    #+#             */
/*   Updated: 2025/08/31 15:20:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void print_msg(const char *env)
{
    printf("cheguei em print_msg com env: %s\n", env);
    if (ft_strncmp(env, "$PWD", ft_strlen(env + 1))  == 0
        || ft_strncmp(env, "$OLDPWD", ft_strlen(env + 1)) == 0
        || ft_strncmp(env, "$HOME", ft_strlen(env + 1)) == 0)
        write(2, " Is a directory\n", 16);
    if (ft_strncmp(env, "$USER", ft_strlen(env + 1))  == 0
        || ft_strncmp(env, "$LOGNAME", ft_strlen(env + 1)) == 0)
        write(2, ": command not found\n", 21);
    else
        write(2, ": No such file or directory\n", 29);    
}

static void is_expandable(char *input, char *var_value)
{
	static const char	*expandable_envs[] = {"$PATH", "$PWD", "$OLDPWD",
        "HOME", "$USER", "$LOGNAME", NULL};
	int					i;

	printf("cheguei em is_expandable com input: %s e var_value: %s\n", input, var_value);
    i = -1;
	while (expandable_envs[++i])
	{
		if (ft_strncmp(input, expandable_envs[i], ft_strlen(expandable_envs[i]) + 1) == 0)
		{
            write(1, var_value, ft_strlen(var_value));
            break ;
        }
	}
	print_msg(expandable_envs[i]);
    return ;
}

static void call_exec(t_minishell *mini, char *var_value)
{
    t_process *p;

    printf("cheguei em call_exec com input: %s\n", mini->input);
    p = new_process(var_value);
    if (!p)
        safe_exit(mini);
    mini->process_list = p;
    if (is_cmd(var_value, mini))
    {
        p->path = path_name(paths(mini->env_list), var_value);
        p->tokens = new_token(ft_strdup(var_value), CMD, mini);
    }
    else
        p->tokens = new_token(ft_strdup(var_value), BUILTIN, mini);
    executor(mini);
}

void    expand_env_vars(t_minishell *mini)
{
    int     i;
    char    *input;
    char    *var_value;

    i = 0;
    input = mini->input;
    printf("cheguei em expand_env_vars com input: %s\n", input);
    while (is_stopchar(input[++i]))
        ;
    if (!ft_isspace(input[i]) && input[i] != '\0')
        return ;
    var_value = extract_variable(mini, input);
    if (!var_value)
        return ;
    is_expandable(mini->input, var_value);
    if (is_builtin(mini->input) || is_cmd(mini->input, mini))
        call_exec(mini, var_value);
    
}