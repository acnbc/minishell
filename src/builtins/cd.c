/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:42:44 by abouchat          #+#    #+#             */
/*   Updated: 2025/09/06 15:50:05 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	change_cwd(t_env *env_list)
{
	t_env	*old_pwd;
	t_env	*pwd;
	char	*temp;

	old_pwd = find_env_var("OLDPWD", env_list);
	pwd = find_env_var("PWD", env_list);
	if (!old_pwd || !pwd)
		return ;
	free(old_pwd->var_cont);
	old_pwd->var_cont = ft_strdup(pwd->var_cont);
	free(pwd->var_cont);
	temp = getcwd(NULL, 0);
	pwd->var_cont = ft_strdup(temp);
	free(temp);
}

static char	*cd_special_char(char *str, t_env *env_list)
{
	t_env	*old_pwd;
	t_env	*home_path;
	char	*path;

	path = NULL;
	if (str[0] == '/')
		path = ft_strdup(str);
	else if (str[0] == '-')
	{
		old_pwd = find_env_var("OLDPWD", env_list);
		if (!old_pwd->var_cont)
			write (2, "cd: OLDPWD not set\n", 19);
		else
			path = ft_strdup(old_pwd->var_cont);
	}
	else if (str[0] == '~')
	{
		home_path = find_env_var("HOME", env_list);
		if (!home_path->var_cont)
			write (2, "cd: HOME not set\n", 17);
		path = ft_strjoin(home_path->var_cont, str + 1);
	}
	else
		path = ft_strdup(str);
	return (path);
}

int	ft_cd(t_minishell *mini, t_env *env_list)
{
	char	*path;
	char	*str;

	str = mini->cur_proc->args[1];
	if (!str)
		return (EXIT_FAILURE);
	path = cd_special_char(str, env_list);
	if (chdir(path) == -1)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	else
		change_cwd(env_list);
	free(path);
	return (EXIT_SUCCESS);
}
