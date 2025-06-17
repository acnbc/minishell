NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I./libft
LDFLAGS = -L./libft
LDLIBS = -lft -lreadline -ltermcap

SRC = main.c parser.c ft_separate.c list_utils.c handle_quotes.c
OBJ = $(SRC:.c=.o)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(LIBFT):
	make bonus -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all
