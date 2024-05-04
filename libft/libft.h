/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: txisto-d <txisto-d@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 05:12:47 by txisto-d          #+#    #+#             */
/*   Updated: 2023/10/16 19:48:41 by txisto-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H
# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

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
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);

//Bonus
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}			t_list;

void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
//printf

typedef struct s_arg
{
	int		width;
	int		minus;
	int		precision;
	int		zero;
	int		plus;
	int		space;
	int		hash;
	int		dot;
	int		specifier;
}			t_arg;

typedef struct s_string
{
	size_t	len;
}			t_string;

int		ft_printf(const char *format, ...);
void	ft_print_c(t_arg *arg, t_string *string, va_list lst);
void	ft_print_d(t_arg *arg, t_string *string, va_list lst);
void	ft_print_p(t_arg *arg, t_string *string, va_list lst);
void	ft_print_s(t_arg *arg, t_string *string, va_list lst);
void	ft_print_u(t_arg *arg, t_string *string, va_list lst);
void	ft_print_x(t_arg *arg, t_string *string, va_list lst);
void	ft_print_xx(t_arg *arg, t_string *string, va_list lst);
int		ft_converter(const char *format, va_list lst, t_string *string);
int		ft_printlen(const char *str);
int		ft_flaglen(const char *str);
void	ft_printchar(char c, t_string *string);
void	ft_printstr(const char *s, t_string *string);
void	ft_printstr_ltda(const char *s, t_string *string);
char	*ft_ptoa(unsigned long n);
char	*ft_utoa(unsigned int n);
char	*ft_xtoa(unsigned int n);
char	*ft_xxtoa(unsigned int n);
int		ft_specif(char specifier, char *flags, va_list lst, t_string *string);

// GET_NEXT_LINE

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

char	*get_next_line(int fd);
char	*ft_getting(int fd, char *line);
char	*ft_cut(char *line);
char	*ft_update(char *line);
size_t	ft_linelen(char *str);
char	*ft_strjoin_nl(char *s1, char *s2);
int		ft_eol(char *str);
char	*ft_strncpy(char *dest, char *src, size_t len);

// MY_EXTRAS

size_t	ft_line_no_n(char *str);
int		find_char(char c, char *find);
int		free_splits(char **line);
int		ft_strcmp(char *s1, char *s2);
int		quotes_open(char *str, int target_index);
#endif
