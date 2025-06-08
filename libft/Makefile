NAME = libft.a
CC = cc
CCFLAGS = -Wall -Wextra -Werror -I ./
SRC = ft_atoi.c ft_isdigit.c ft_memmove.c ft_split.c ft_strlcpy.c ft_strtrim.c ft_bzero.c \
ft_isprint.c ft_memset.c ft_strchr.c ft_strlen.c ft_substr.c ft_calloc.c ft_itoa.c \
ft_putchar_fd.c ft_strdup.c ft_strmapi.c ft_tolower.c ft_isalnum.c ft_memchr.c ft_putendl_fd.c \
ft_striteri.c  ft_strncmp.c  ft_toupper.c \
ft_isalpha.c ft_memcmp.c ft_putnbr_fd.c ft_strjoin.c ft_strnstr.c \
ft_isascii.c ft_memcpy.c ft_putstr_fd.c ft_strlcat.c ft_strrchr.c \
ft_printf.c ft_printf_utils.c ft_printf_utils2.c ft_printf_utils3.c get_next_line.c get_next_line_utils.c
SRC_BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
OBJS := $(SRC:%.c=%.o)
OBJS_BONUS := $(SRC_BONUS:%.c=%.o)
OBJS_ALL = $(OBJS) $(OBJS_BONUS)

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus: $(OBJS_ALL)
	ar rcs $(NAME) $(OBJS_ALL)

%.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $<

.PHONY: clean
clean:
	rm -f $(OBJS_ALL)

fclean: clean
	rm -f $(NAME)

re: clean all
