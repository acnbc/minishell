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
# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

typedef struct s_env
{
	char				*env_var;
	struct s_env		*next;
}						t_env;

typedef struct s_process
{
	char				*cmd_seq;
	struct s_process	*next;
}						t_process;

typedef struct s_minishell
{
	char				*input;
	t_env				*env_list;
	char				**envp_copy;
	t_process			*process_list;
}						t_minishell;

/* ----------------------------- PARSER ---------------------------*/
t_process				*new_process(char *content);
void					add_process(t_process **lst, t_process *new);
int						ft_isspace(char c);
void					parser(t_minishell *minishell);
char					*extract_variable(t_minishell *minishell,
							char *variable);
char					*handle_quotes(t_minishell *minishell);
t_process				*separate_process(char *input);
char					*ft_strjoin_free(char *s1, char *s2);
void					*safe_malloc(size_t bytes);
void					free_env(char **envp_copy, int i);
int						is_stopchar(char c);
char					*expansion(t_minishell *minishell);
char					*get_env_var(t_minishell *minishell, int *i, int *j);
void					free_env_list(t_env *env_list);
void					env_lstadd_back(t_env **lst, t_env *new);
t_env					*env_lstnew(char *env_var);
t_env					*env_list(char *envp[]);
char					**copy_envp(t_env *env_list);
/* ----------------------------- UTILS ---------------------------*/

/* ----------------------------- FREE MEMORY ---------------------------*/
void					free_process_list(t_process *process_list);
void					free_env_list(t_env *env_list);
void					free_env(char **envp_copy, int i);

void					print_process_list(t_process *process_list);
void					print_env_list(t_env *env_list);

#endif