/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 13:49:59 by codespace         #+#    #+#             */
/*   Updated: 2025/08/31 16:08:50 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_msg(const char *env)
{
	if (ft_strncmp(env, "$PWD", ft_strlen(env + 1)) == 0 || ft_strncmp(env,
			"$OLDPWD", ft_strlen(env + 1)) == 0 || ft_strncmp(env, "$HOME",
			ft_strlen(env + 1)) == 0)
		write(2, " Is a directory\n", 16);
	if (ft_strncmp(env, "$USER", ft_strlen(env + 1)) == 0 || ft_strncmp(env,
			"$LOGNAME", ft_strlen(env + 1)) == 0)
		write(2, ": command not found\n", 21);
	else
		write(2, ": No such file or directory\n", 29);
}

static void	is_expandable(char *input, char *var_value)
{
	static const char	*expandable_envs[] = {"$PATH", "$PWD", "$OLDPWD",
		"$HOME", "$USER", "$LOGNAME", NULL};
	int					i;

	i = -1;
	while (expandable_envs[++i])
	{
		if (ft_strncmp(input, expandable_envs[i],
				ft_strlen(expandable_envs[i])) == 0)
		{
			write(1, var_value, ft_strlen(var_value));
			break ;
		}
	}
	if (expandable_envs[i])
		print_msg(expandable_envs[i]);
	g_exit_status = 0;
	return ;
}

static void	call_exec(t_minishell *mini, char *var_value)
{
	t_process	*p;

	p = new_process(var_value);
	if (!p)
		safe_exit(mini);
	mini->process_list = p;
	mini->cur_proc = p;
	if (is_cmd(var_value, mini))
		p->tokens = new_token(ft_strdup(var_value), CMD, mini);
	else
		p->tokens = new_token(ft_strdup(var_value), BUILTIN, mini);
	executor(mini);
}

static int	expand_exit_status(t_minishell *mini)
{
	char	*status;

	status = ft_itoa(g_exit_status);
	if (ft_strncmp(mini->input, "$?", ft_strlen(mini->input) + 1) == 0)
	{
		write(2, status, ft_strlen(status) + 1);
		g_exit_status = 0;
		return (1);
	}
	return (0);
}

void	expand_env_vars(t_minishell *mini)
{
	int		i;
	char	*var_value;
	char	*var_name;

	i = 1;
	if (!is_stopchar(mini->input[i]))
		return ;
	if (expand_exit_status(mini))
		return ;
	while (mini->input[i] && is_stopchar(mini->input[i]))
		i++;
	var_name = ft_substr(mini->input, 1, i - 1);
	if (!var_name)
		return ;
	if (mini->input[i] && !ft_isspace(mini->input[i]))
	{
		free(var_name);
		return ;
	}
	var_value = extract_variable(mini, var_name);
	if (!var_value)
		return ;
	is_expandable(mini->input, var_value);
	call_exec(mini, var_value);
}
