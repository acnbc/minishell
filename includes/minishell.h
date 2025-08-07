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

extern int g_exit_status;

typedef struct s_exec_vars
{
	int					tmpin;
	int					tmpout;
	int					fdin;
	int					fdout;
	int					pid;
	int					fdpipe[2];
	int					ret;
}						t_exec_vars;

enum					e_token_type
{
	BUILTIN,
	CMD,
	ARGS,
};

typedef struct s_env_vars
{
	char				*equal_sign;
	char				*var_name;
	char				*var_cont;
}						t_env_vars;

typedef struct s_env
{
	char				*var_name;
	char				*var_cont;
	struct s_env		*next;
	struct s_env		*prev;
}						t_env;

typedef struct s_token
{
	char				*value;
	enum e_token_type	type;
	struct s_token		*next;
}						t_token;

typedef struct s_process
{
	char				*cmd_seq;
	int					process_num;
	t_token				*tokens;
	char				*path;
	char				*input_file;
	char				*output_file;
	char				*heredoc_delimiter;
	int					append_flag;
	int					redirect_in_flag;
	int					redirect_out_flag;
	int					heredoc_flag;
	int					heredoc_quote_flag;
	int					double_quote_flag;
	int					single_quote_flag;
	char				**args;
	bool				found_cmd;
	int					fdin;
	int					fdout;
	int					pid;
	int					status;
	int					exit_signal;
	struct s_process	*next;
}						t_process;

typedef struct s_minishell
{
	char				*input;
	t_env				*env_list;
	char				**envp_copy;
	int					process_count;
	t_process			*process_list;
	t_process			*current_process;
	t_exec_vars			exec_vars;
}						t_minishell;

/* ----------------------------- PARSER ---------------------------*/
t_process				*new_process(char *content);
void					add_process(t_process **lst, t_process *new);
t_process				*last_process(t_process *proc);
int						ft_isspace(char c);
int						parser(t_minishell *minishell);
char					*extract_variable(t_minishell *minishell,
							char *variable);
char					*handle_quotes(t_minishell *minishell, char *process,
							int *i);
int						is_between_quotes(const char *str, int pos);
t_process				*separate_process(char *input);
int						count_process(t_process *process_list);
char					*ft_strjoin_free(char *s1, char *s2);
int						is_stopchar(char c);
char					*expansion(t_minishell *minishell, char *segment);
char					*get_env_var(t_minishell *minishell, char *segment,
							int *i, int *j);
void					free_env_list(t_env *env_list);
void					env_lstadd_back(t_env **lst, t_env *new);
t_env					*env_lstnew(char *var_name, char *var_cont);
// t_env					*env_lstnew(char *env_var);
t_env					*env_list(char *envp[]);
char					**copy_envp(t_env *env_list);
int						verify_quote_pair(char *input, char quote, int *i);
int						verify_quote_count(char *process);
/* ----------------------------- SAFE OPERATIONS -----------------*/
void					safe_exit(t_minishell *minishell);
void					*safe_malloc(size_t bytes);
char					*ft_substr_safe(char *s, unsigned int start, size_t len,
							t_minishell *minishell);
/* ----------------------------- LEXER ---------------------------*/
void					lexer(t_minishell *minishell);
void					tokenize(t_minishell *minishell);
int						is_builtin(char *cmd);
char					*is_variable(t_minishell *minishell, int *i, int start);
void					word_tokenizer(t_minishell *minishell, int *i);
void					redin_heredoc_tokenizer(t_minishell *minishell, int *i);
void					redout_append_tokenizer(t_minishell *minishell, int *i);
void					get_word_token(t_minishell *minishell, int *i,
							int start);
char					**paths(t_env *env_list);
char					*path_name(char **paths, char *command);
/* ---------------- SYNTACTIC ANALYSIS ------------------*/
bool					syntactic_analysis(t_minishell *minishell);
int						is_cmd(char *cmd, t_minishell *minishell);
/*------------------------ EXECUTOR ------------------------------*/
void					executor(t_minishell *minishell);
void    				handle_heredoc(t_minishell *mini);
void					unlink_heredoc_files(t_minishell *minishell);
char					**copy_args(t_token *tokens);
int						get_args(t_process *process_list);
/* ----------------------------- UTILS ---------------------------*/
t_token					*new_token(char *value, enum e_token_type type,
							t_minishell *minishell);
void					token_lstadd_back(t_token **tokens, t_token *new);
int						skip_spaces(char *str, int *i);
char					*get_str(char *str, int *i, t_minishell *minishell);

/* ----------------------------- FREE MEMORY ---------------------------*/
void					free_process_list(t_process *process_list);
void					free_env_list(t_env *env_list);
void					free_env(char **envp_copy);
void					free_token_list(t_token *tokens);
void					free_matrix(char **matrix);
void					safe_env_list_exit(t_env_vars *vars, t_env *env_list);
void					flush(t_minishell *minishell);

void					print_process_list(t_process *process_list);
void					print_env_list(t_env *env_list);

#endif