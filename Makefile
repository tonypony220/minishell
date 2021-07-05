dir		=   .

SRCS	=	fork.c multalloc.c find_path.c builtins.c dict_func.c environ.c exiting.c term.c

#LIB_EXTENSIONS	= ft_str_in_strs.c

OBJS	=	${SRCS:.c=.o}

CFLAGS	=   -O0 -g # -Wall -Wextra -Werror #-g #-fsanitize=address

HEAD	=	minishell.h

CC		=	gcc

RM		=	-rm	-f

NAME	=	a.out

SUBDIRS := libft 
#
TOPTARGETS := all clean fclean

$(TOPTARGETS): $(SUBDIRS)
#
#$(libs): $(SUBDIRS)

$(SUBDIRS):
		$(MAKE) -C $@ $(MAKECMDGOALS)

#%.o: %.c $(HEAD)
#		$(CC) -Imlx -Ignl -Ilibft ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS} ${HEAD}
		$(CC) ${OBJS} -Llibft -lft -lreadline -ltermcap -o ${NAME}

all:	${NAME}

clean: $(SUBDIRS)
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re:     fclean	all

.PHONY:	re bonus all clean fclean $(SUBDIRS) $(TOPTARGETS)
