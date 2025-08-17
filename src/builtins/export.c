/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:46:54 by abouchat          #+#    #+#             */
/*   Updated: 2025/08/17 17:49:01 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**first_equal(char *args)
{
	while (*args)
	{
		if (*args == '=')
	}
}

static void	update_args(char *arg_name, char *arg_cont, char *args)
{
	char	**curr;
	curr = ft_split(args, '=');
}

int	ft_export(t_env *env_list, char **args)
{
	t_env	*temp_node;
	char	*arg_name;
	char	*arg_cont;

	while (!args)
	{
		update_args(arg_name, arg_cont, *args);
		if (arg_name == NULL)
			write(2, "export: not a valid identifier\n", 32);
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
		args++;
	}
	return (EXIT_SUCCESS);
}

t_env	*find_env_var(char *var, t_env *env_list)
{
	t_env	*curr;

	curr = env_list;
	while (curr)
	{
		if (!ft_strncmp(var, curr->var_name, ft_strlen(var)))
			break ;
		curr = curr->next;
	}
	return (curr);
}

