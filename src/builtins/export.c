/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:46:54 by abouchat          #+#    #+#             */
/*   Updated: 2025/08/24 15:59:14 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	free_func(char **arg1, char **arg2)
{
	free(*arg1);
	free(*arg2);
}

static char	**first_equal(char *arg)
{
	int		i;
	char	**sep_args;

	if (!arg)
		return (NULL);
	sep_args = (char **)ft_calloc(3, sizeof(char *));
	if (!sep_args)
		return (NULL);
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
		{
			if (i != 0)
				sep_args[0] = ft_substr(arg, 0, i);
			sep_args[1] = ft_substr(arg, i + 1, ft_strlen(arg) - i);
			break ;
		}
		i++;
	}
	return (sep_args);
}

static int	update_args(char **arg_name, char **arg_cont, char *args)
{
	char	**curr;

	curr = first_equal(args);
	if (!curr)
		return (0);
	free(*arg_name);
	free(*arg_cont);
	*arg_name = ft_strdup(curr[0]);
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

	arg_name = NULL;
	arg_cont = NULL;
	while (++args && *args)
	{
		if (!update_args(&arg_name, &arg_cont, *args))
			return (EXIT_FAILURE);
		if (arg_name == NULL)
			write(2, "export: not a valid identifier\n", 32);
		update_env_var(env_list, arg_name, arg_cont);
	}
	free_func(&arg_cont, &arg_name);
	return (EXIT_SUCCESS);
}
