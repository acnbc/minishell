/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 16:39:34 by abouchat          #+#    #+#             */
/*   Updated: 2025/07/09 19:33:33 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc < 2)
		return (0);

	t_env *env_head = env_list(envp); //dando leak?
	ft_env(env_head);
	write(1, "\n\n\n", 3);
	ft_export(argv[1], env_head);
	ft_env(env_head);
	write(1, "\n\n\n", 3);
	ft_unset(argv[2], env_head);
	ft_env(env_head);
	ft_pwd(env_head);
	free_env_list(env_head);

}
