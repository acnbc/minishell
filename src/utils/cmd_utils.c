/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:45:00 by anogueir          #+#    #+#             */
/*   Updated: 2025/08/24 16:04:36 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_path_executable(char *cmd, t_minishell *mini)
{
	struct stat	path_stat;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
		{
			if (stat(cmd, &path_stat) == 0)
			{
				if (S_ISREG(path_stat.st_mode))
				{
					mini->cur_proc->path = ft_strdup(cmd);
					return (1);
				}
			}
		}
		return (0);
	}
	return (-1);
}

static int	check_path_dirs(char *cmd, t_minishell *mini)
{
	char		**path_dirs;
	char		*temp;

	if (ft_strncmp(cmd, "..", 3) == 0)
		return (0);
	path_dirs = paths(mini->env_list);
	if (!path_dirs)
		return (0);
	temp = path_name(path_dirs, cmd);
	if (temp)
	{
		mini->cur_proc->path = temp;
		free_matrix(path_dirs);
		return (1);
	}
	free_matrix(path_dirs);
	return (0);
}

int	is_cmd(char *cmd, t_minishell *mini)
{
	int	result;

	result = check_path_executable(cmd, mini);
	if (result != -1)
		return (result);
	return (check_path_dirs(cmd, mini));
}

int	is_builtin(char *segment)
{
	static const char	*builtins[] = {"echo", "cd", "pwd", "export", "unset",
		"env", "exit", NULL};
	int					i;

	i = -1;
	if (!segment)
		return (0);
	while (builtins[++i])
	{
		if (ft_strncmp(segment, builtins[i], ft_strlen(builtins[i]) + 1) == 0)
			return (1);
	}
	return (0);
}
