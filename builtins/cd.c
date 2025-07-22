/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:42:44 by abouchat          #+#    #+#             */
/*   Updated: 2025/07/22 18:16:00 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*cd -: Volta para o diretório anterior (onde você estava antes do último cd).

cd /: Vai para o diretório raiz do sistema de arquivos.

cd ~: Vai para o diretório inicial do usuário atual. 
*/

#include "../minishell.h"

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
			return (NULL) ;//adicionar func de mensagem de erro
		else
			path = ft_strjoin(old_pwd->var_cont, str + 1);
	}
	if (str[0] == '~')
	{
		home_path = find_env_var("HOME", env_list);
		if (!home_path->var_cont)
			return (NULL);//adicionar func de mensagem de erro
		path = ft_strjoin(home_path->var_cont, str + 1);
	}
	else
		path = ft_strdup(str);
	return (path);
}

void	ft_cd(char *str, t_env *env_list)
{
	char	*path;
	t_env	*old_pwd;
	t_env	*pwd;
	char	*temp;

	path = cd_special_char(str, env_list);
	if (!path)
		path = ft_strdup(str);
	old_pwd = find_env_var("OLDPWD", env_list);
	pwd = find_env_var("PWD", env_list);
	if (chdir(path) == -1)
	{
		write(1, "cd: No such file or directory\n", 30);
		return ;
	}
	else
	{
		free(old_pwd->var_cont);
		old_pwd->var_cont = ft_strdup(pwd->var_cont);
		free(pwd->var_cont);
		pwd->var_cont = NULL;
		temp = getcwd(pwd->var_cont, 4096);
		pwd->var_cont = ft_strdup(temp);
		free(temp);
	}
	free(path);
}

