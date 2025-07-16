/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:42:44 by abouchat          #+#    #+#             */
/*   Updated: 2025/07/16 18:31:37 by abouchat         ###   ########.fr       */
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
	t_env	*pwd;
	char	*path;

	if (str[0] == '/')
		path = ft_strdup(str);
	if (str[0] == '-')
	{
		old_pwd = find_env_var("OLDPWD", env_list);
		if (!old_pwd->var_cont)
			return ;//adicionar func de mensagem de erro
		else
			path = ft_strjoin(old_pwd->var_cont, str);
	}
	if (str[0] == '~')
	{
		home_path = find_env_var("HOME", env_list);
		if (!home_path->var_cont)
			return ;//adicionar func de mensagem de erro
		path = ft_strjoin(home_path->var_cont, str);
	}
	return (path);
}

static int	check_relative(char *str, t_env *env_list)
{
	if (!ft_strnstr(str, ".", 1) || !(ft_strnstr(str, "..", 2)))
	{
		return (0);
	}
	return (1);
}

void	ft_cd(char *str, t_env *env_list)
{
	char	*path;

	if (!str)
		return ;
	if (check_relative(str, env_list == 0))
		path = cd_special_char(str, env_list);
	else
	{
		
	}
}

