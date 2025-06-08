/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchat <abouchat@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 19:05:10 by abouchat          #+#    #+#             */
/*   Updated: 2025/05/04 17:06:34 by abouchat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# define BUFFER_SIZE 3

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

int		ft_atoi(const char *nptr);

void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t nmemb, size_t size);

int		ft_isalnum(int c);

int		ft_isalpha(int c);

int		ft_isascii(int c);

int		ft_isdigit(int c);

int		ft_isprint(int c);

char	*ft_itoa(int n);

void	*ft_memchr(const void *s, int c, size_t n);

int		ft_memcmp(const void *s1, const void *s2, size_t n);

void	*ft_memcpy(void *dest, const void *src, size_t n);

void	*ft_memmove(void *dest, const void *src, size_t n);

void	*ft_memset(void *s, int c, size_t n);

void	ft_putchar_fd(char c, int fd);

void	ft_putendl_fd(char *s, int fd);

void	ft_putnbr_fd(int n, int fd);

void	ft_putstr_fd(char *s, int fd);

char	**ft_split(char const *s, char c);

char	*ft_strchr(const char *s, int c);

char	*ft_strdup(const char *s);

void	ft_striteri(char *s, void (*f)(unsigned int, char *));

char	*ft_strjoin(const char *s1, char const *s2);

size_t	ft_strlcat(char *dst, char const *src, size_t size);

size_t	ft_strlcpy(char *dst, char const *src, size_t size);

size_t	ft_strlen(const char *s);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_strnstr(const char *big, const char *little, size_t len);

char	*ft_strrchr(const char *s, int c);

char	*ft_strtrim(char const *s1, char const *set);

char	*ft_substr(char const *s, unsigned int start, size_t len);

int		ft_tolower(int c);

int		ft_toupper(int c);

t_list	*ft_lstnew(void *content);

void	ft_lstadd_front(t_list **lst, t_list *new);

t_list	*ft_lstlast(t_list *lst);

void	ft_lstadd_back(t_list **lst, t_list *new);

int		ft_lstsize(t_list *lst);

void	ft_lstdelone(t_list *lst, void (*del)(void *));

void	ft_lstclear(t_list **lst, void (*del)(void *));

void	ft_lstiter(t_list *lst, void (*f)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

int		ft_printf(const char *format, ...);

int		check_next_letter(char c, va_list args);

int		ft_num_len(long n, int base);

int		ft_num_len_unsigned(unsigned long n, int base);

int		ft_putchar_args(int c);

int		ft_putstr_args(char *str);

int		ft_putnbr_args(int n);

int		ft_print_hex_args(unsigned long n, int base_case);

void	ft_puthex(unsigned long num, char *base);

int		ft_putaddr_args(void *addr);

void	ft_put_unsigned(unsigned int n);

int		ft_putunsign_args(unsigned int n);

void	split_free(char **arr, int i);

int		count_words(char const *s, char c);

char	*get_next_line(int fd);

char	*gnl_substr(char const *s, unsigned int start, size_t len);

size_t	gnl_strlen(const char *s);

char	*gnl_strjoin(const char *s1, const char *s2);

int		gnl_strchr(const char *s, int c);

char	*gnl_strdup(const char *s);

#endif
