SRCS	=	 ft_strlen.c ft_atoi.c ft_strrchr.c \
ft_bzero.c ft_isalpha.c ft_memset.c \
ft_memcpy.c ft_memccpy.c ft_memmove.c ft_isdigit.c ft_strlcpy.c \
ft_isprint.c ft_strlcat.c ft_memchr.c ft_strchr.c ft_strnstr.c \
ft_strncmp.c ft_isalnum.c ft_isascii.c ft_toupper.c ft_tolower.c \
ft_calloc.c ft_strdup.c ft_memcmp.c ft_substr.c ft_strjoin.c \
ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c \
ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_str_in_strs.c ft_strcmp.c \
ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
ft_lst_find.c ft_lst_rm.c ft_list_remove_if.c ft_lst_sort_bubble.c \
ft_lst_to_strs.c ft_strjoind.c ft_lstiter_arg.c
#SRCS_BONUS =
 

OBJS	=	${SRCS:.c=.o}

OBJS_B	=	${SRCS_BONUS:.c=.o}

CFLAGS	= -O0 -g -Wall -Wextra -Werror

HEAD	=	libft.h

CC		=	gcc

RM		=	rm	-f

NAME	=	libft.a

.c.o: 	
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o} 

${NAME}:	${OBJS}
		ar rcs ${NAME} ${OBJS}

bonus:	${OBJS} ${OBJS_B}
		ar rcs ${NAME} ${OBJS} ${OBJS_B}

all:	${NAME}

clean:
		${RM} ${OBJS} ${OBJS_B}


fclean: clean
	${RM}	${NAME}

re:		fclean	all

.PHONY:	re	bonus	all	clean	fclean

