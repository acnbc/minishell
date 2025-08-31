# ========== Basic Configuration ==========
NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I./includes -I./libft/includes
LDFLAGS		= -L./libft
LDLIBS		= -lft -lreadline -ltermcap

# ========== Source Files ==========
SRC_DIR		= src
SRC_SUBDIRS	= builtins exec parse utils

SRC			= main.c mini_shell.c \
			  $(addprefix parser/, parser.c handle_quotes.c expansion.c separate_process.c lexer.c \
			  word_tokenizer.c syntactic_analysis.c env_var.c) \
			  $(addprefix exec/, executor.c heredoc.c exec_tools.c) \
			  $(addprefix builtins/, cd.c echo.c env.c export.c pwd.c unset.c ) \
			  $(addprefix utils/, process_utils.c utils.c env_utils.c safe_exit.c token_utils.c \
			  lexer_utils.c quotes_utils.c string_utils.c exec_utils.c redirect_utils.c safe_utils.c \
			  heredoc_utils.c cmd_utils.c export_utils.c tokenizer_utils.c) \

OBJ_DIR		= obj
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# ========== Libft Configuration ==========
LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

# ========== Rules ==========
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	@echo "✅ $(NAME) compiled successfully!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make bonus -C $(LIBFT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@echo "🧹 Object files removed!"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "🧹🧹 $(NAME) and libft fully cleaned!"

re: fclean all

.PHONY: all clean fclean re