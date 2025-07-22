/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 16:36:20 by anogueir          #+#    #+#             */
/*   Updated: 2025/07/22 17:44:26 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <readline/readline.h>
# include <term.h>
# include <curses.h>
# include <limits.h>
# include "libft/libft.h"

typedef struct s_env
{
	char				*var_name;
	char				*var_cont;
	struct s_env		*next;
	struct s_env		*prev;
}						t_env;


typedef struct s_shelldata
{
	char	*home_path;
	char	*pwd;
}				t_shelldata;


void	ft_echo(char **args, int fd);
void	ft_export(char *arg_name, char *arg_cont, t_env *env_list);
void	ft_env(t_env *env_list);
void	ft_unset(char *var, t_env *env_list);
void	ft_pwd(t_env *env_list);
void	ft_cd(char *str, t_env *env_list);
t_env	*env_lstnew(char *var_name, char *var_cont);
void	env_lstadd_back(t_env **lst, t_env *new);
t_env	*env_list(char *envp[]);
void	*safe_malloc(size_t bytes);
t_env	*find_env_var(char *var, t_env *env_list);
void	free_env_list(t_env *env_list);

#endif