/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:46:54 by abouchat          #+#    #+#             */
/*   Updated: 2025/08/31 16:13:25 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	stopchar_loop(char **sep_args, char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!is_stopchar(arg[i]) && arg[i] != '=')
		{
			sep_args[0] = NULL;
			sep_args[1] = NULL;
			break ;
		}
		if (arg[i] == '=')
		{
			if (i != 0)
				sep_args[0] = ft_substr(arg, 0, i);
			sep_args[1] = ft_substr(arg, i + 1, ft_strlen(arg) - i);
			break ;
		}
		i++;
	}
}

static char	**first_equal(char *arg)
{
	char	**sep_args;

	if (!ft_strchr(arg, '='))
		return (NULL);
	sep_args = (char **)ft_calloc(3, sizeof(char *));
	if (!sep_args)
		return (NULL);
	stopchar_loop(sep_args, arg);
	return (sep_args);
}

static int	update_args(char **arg_name, char **arg_cont, char *args)
{
	char	**curr;

	free(*arg_name);
	free(*arg_cont);
	*arg_name = NULL;
	*arg_cont = NULL;
	curr = first_equal(args);
	if (!curr)
		return (0);
	if (curr[0])
		*arg_name = ft_strdup(curr[0]);
	if (curr[1])
		*arg_cont = ft_strdup(curr[1]);
	free(curr[0]);
	free(curr[1]);
	free(curr);
	return (1);
}

static int	update_env_var(t_env *env_list, char *arg_name, char *arg_cont)
{
	t_env	*temp_node;

	if (find_env_var(arg_name, env_list))
	{
		temp_node = find_env_var(arg_name, env_list);
		free(temp_node->var_cont);
		temp_node->var_cont = ft_strdup(arg_cont);
	}
	else
	{
		temp_node = env_lstnew(ft_strdup(arg_name), ft_strdup(arg_cont));
		env_lstadd_back(&env_list, temp_node);
	}
	return (1);
}

int	ft_export(t_env *env_list, char **args)
{
	char	*arg_name;
	char	*arg_cont;
	int		exit_s;

	exit_s = 0;
	arg_name = NULL;
	arg_cont = NULL;
	while (++args && *args)
	{
		if (!update_args(&arg_name, &arg_cont, *args))
			continue ;
		if (arg_name == NULL)
		{
			write(2, "export: not a valid identifier\n", 32);
			exit_s = EXIT_FAILURE;
			continue ;
		}
		update_env_var(env_list, arg_name, arg_cont);
	}
	free(arg_cont);
	free(arg_name);
	return (exit_s);
}
