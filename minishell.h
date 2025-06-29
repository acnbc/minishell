/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 16:36:20 by anogueir          #+#    #+#             */
/*   Updated: 2025/06/29 16:55:33 by abouchat         ###   ########.fr       */
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
# include "libft/libft.h"

typedef struct s_env_node
{
	char				var[200];
	struct s_env_node	*next;
}				t_env_node;

typedef struct s_shelldata
{
	char	*home_path;
	char	*pwd;
}				t_shelldata;


void	ft_echo(char **args, int fd);

#endif