dir		=   .

SRCS	=	fork.c multalloc.c find_path.c builtins.c dict_func.c environ.c exiting.c main.c #term.c 

P_DIR	= 	pars/

PARSERS	=	${P_DIR}mini_parser.c \
			${P_DIR}error_out.c \
			${P_DIR}ft_list_utils.c \
			${P_DIR}env_func.c \
			${P_DIR}parsers.c \
			${P_DIR}command.c \
			${P_DIR}util.c 

OBJS	=	${SRCS:.c=.o}

P_OBJS  =   ${PARSERS:.c=.o}


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

${NAME}: ${OBJS} ${P_OBJS} ${HEAD}
		$(CC) ${OBJS} ${P_OBJS} -Llibft -lft -lreadline -o ${NAME}
#$(CC) ${OBJS} ${P_OBJS} -Llibft -lft -lreadline -ltermcap -o ${NAME}

all:	${NAME}

clean: $(SUBDIRS)
		${RM} ${OBJS} ${P_OBJS}

fclean: clean
		${RM} ${NAME}

re:     fclean	all

.PHONY:	re bonus all clean fclean $(SUBDIRS) $(TOPTARGETS)
