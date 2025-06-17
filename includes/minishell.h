/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anogueir <anogueir@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 16:36:20 by anogueir          #+#    #+#             */
/*   Updated: 2025/06/08 16:36:25 by anogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

# define MINISHELL_PROMPT "minishell> "
# define SINGLE_QUOTE "'"
# define DOUBLE_QUOTE "\""

typedef struct s_process
{
	char				*cmd_seq;
	struct s_process	*next;
}						t_process;

typedef struct s_minishell
{
	char				**envp_copy;
	char				*input;
}						t_minishell;

typedef struct s_expansion
{
	int					i;
	int					start;
	int					str_i;
	char				*var_name;
}						t_expansion;

t_process				*ft_separate(char *input);
t_process				*new_process(char *content);
void					add_process(t_process **lst, t_process *new);
int						ft_isspace(char c);
void					parser(t_minishell *minishell);

void					print_process_list(t_process *process_list);
#endif