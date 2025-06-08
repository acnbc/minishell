NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
READLINE_FLAGS = -lreadline -ltermcap
SRC = main.c
OBJ = $(SRC:.c=.o)
LIBFT_PATH = libft/
LIBFT = libft.a
all: $(LIBFT_PATH)$(LIBFT) $(NAME)

$(LIBFT_PATH)$(LIBFT):
	make -C $(LIBFT_PATH)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LIBFT_PATH)$(LIBFT) $(CFLAGS) $(READLINE_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all
