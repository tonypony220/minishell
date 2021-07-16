/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehtel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 22:56:47 by mehtel            #+#    #+#             */
/*   Updated: 2020/11/14 23:01:31 by mehtel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *str, int character, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
char				*ft_strrchr(const char *s, int c);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_isdigit(int c);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strchr(const char *s, int c);
int					ft_isalpha(int c);
char				*ft_strnstr(const char *haystack, \
					const char *needle, size_t len);
int					ft_isalnum(int c);
char				*ft_strdup(const char *src);
int					ft_atoi(char *str);
int					ft_isascii(int c);
int					ft_toupper(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
void				*ft_calloc(size_t count, size_t size);
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putstr_fd(char *s, int fd);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));
char				**ft_lst_to_strs(t_list *lst, char* (*pull_str)());
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

void				ft_lstiter_arg(t_list *lst, void (*f)(), void *data);
void				*ft_lstgen(t_list *lst, void *(*f)(void *));

void				ft_lst_sort_bubble(t_list **lst, int (*cmp)());
t_list				*ft_lst_find(t_list *lst, void *data_ref, int (*cmp)());
void				ft_lst_rm(t_list **lst, void *data_ref,
								int (*cmp)(), void (*del)(void *));
int					ft_str_in_strs(char *needle, char **arr);
int					ft_strcmp(const char *s1, const char *s2);

char				*ft_strjoind(char const *s1, char const *s2,
								 char const *delim);

#endif
