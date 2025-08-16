/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:42:44 by abouchat          #+#    #+#             */
/*   Updated: 2025/08/16 10:30:18 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*cd -: Volta para o diretório anterior (onde você estava antes do último cd).

cd /: Vai para o diretório raiz do sistema de arquivos.

cd ~: Vai para o diretório inicial do usuário atual.
*/

#include "../../includes/minishell.h"

static void	change_cwd(t_env *env_list)
{
	t_env	*old_pwd;
	t_env	*pwd;
	char	*temp;

	old_pwd = find_env_var("OLDPWD", env_list);
	pwd = find_env_var("PWD", env_list);
	free(old_pwd->var_cont);
	old_pwd->var_cont = ft_strdup(pwd->var_cont);
	free(pwd->var_cont);
	pwd->var_cont = NULL;
	temp = getcwd(pwd->var_cont, 4096);
	pwd->var_cont = ft_strdup(temp);
	free(temp);
}

static char	*cd_special_char(char *str, t_env *env_list)
{
	t_env	*old_pwd;
	t_env	*home_path;
	char	*path;

	if (str[0] == '/')
		path = ft_strdup(str);
	if (str[0] == '-')
	{
		old_pwd = find_env_var("OLDPWD", env_list);
		if (!old_pwd->var_cont)
			return (NULL); // adicionar func de mensagem de erro
		else
			path = ft_strjoin(old_pwd->var_cont, str + 1);
	}
	if (str[0] == '~')
	{
		home_path = find_env_var("HOME", env_list);
		if (!home_path->var_cont)
			return (NULL); // adicionar func de mensagem de erro
		path = ft_strjoin(home_path->var_cont, str + 1);
	}
	else
		path = ft_strdup(str);
	return (path);
}

int	ft_cd(t_minishell *mini, t_env *env_list)
{
	char	*path;
	char	*temp;
	char	*str;

	str = mini->cur_proc->args[1];
	path = cd_special_char(str, env_list);
	if (!path)
		path = ft_strdup(str);
	if (chdir(path) == -1)
	{
		write(mini->cur_proc->fdout, "cd: No such file or directory\n", 30);
		return (1);
	}
	else
	{
		change_cwd(env_list);
	}
	free(path);
	return (0);
}
