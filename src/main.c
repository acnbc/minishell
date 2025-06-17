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

char **copy_envp(char *envp[])
{
	int		i;
	int		count;
	char	**envp_copy;

	if (!envp)
		return (NULL);
	envp_copy = NULL;
	count = -1;
	while (envp[++count])
		;
	envp_copy = (char **)safe_malloc(++count * sizeof(char *));
	envp_copy[count] = NULL;
	i = -1;
	while (++i < count)
	{
		envp_copy[i] = ft_strdup(envp[i]);
		if (!envp_copy[i])
			free_env(envp_copy, i);
		return (NULL);
	}
	return (envp_copy);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	*minishell;

	minishell = safe_malloc(sizeof(t_minishell));
	ft_bzero(minishell, sizeof(t_minishell));
	while (1)
	{
		minishell->input = readline(MINISHELL_PROMPT);
		if (!minishell->input)
			continue ;
		minishell->envp_copy = copy_envp(envp);
		parser(minishell);
		//printf("%s\n", input);
	}
}
