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

char	**copy_envp(char *envp[])
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
	if (count == 0)
		return (NULL);
	envp_copy = (char **)safe_malloc(count + 1 * sizeof(char *));
	i = -1;
	while (++i < count)
	{
		envp_copy[i] = ft_strdup(envp[i]);
		if (!envp_copy[i])
		{
			free_env(envp_copy, i);
			return (NULL);
		}
	}
	envp_copy[count] = NULL;
	return (envp_copy);
}

void	print_envp(char **envp_copy)
{
	int	i;

	i = 0;
	if (!envp_copy)
		return ;
	while (envp_copy[i])
	{
		printf("envp_copy[%d]: %s\n", i, envp_copy[i]);
		i++;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	minishell = safe_malloc(sizeof(t_minishell));
	minishell->envp_copy = copy_envp(envp);
	while (1)
	{
		minishell->input = readline(MINISHELL_PROMPT);
		if (!minishell->input)
			continue ;
		parser(minishell);
		// printf("%s\n", input);
	}
}
