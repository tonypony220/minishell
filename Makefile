dir		=   .

SRCS	=	fork.c 				\
			multalloc.c 		\
			find_path.c 		\
			builtins.c  		\
			builtins_2.c  		\
			dict_func.c 		\
			dict_func_2.c 		\
			environ.c   		\
			exiting.c   		\
			main.c 				\
			dispatch_process.c	\
			err.c				\
			process_utils.c		\
			start_process.c		\
			util.c

P_DIR	= 	pars/

PARSERS	=	${P_DIR}mini_parser.c 		\
			${P_DIR}error_out.c 		\
			${P_DIR}ft_list_utils.c 	\
			${P_DIR}env_func.c 			\
			${P_DIR}parsers.c 			\
			${P_DIR}command.c 			\
			${P_DIR}check_cmd.c			\
			${P_DIR}heredoc.c 			\
			${P_DIR}parser_utils.c 		\
			${P_DIR}util.c 

OBJS	=	${SRCS:.c=.o}

P_OBJS  =   ${PARSERS:.c=.o}


CFLAGS	=   -O0 -g  #-Wall -Wextra -Werror #-g #-fsanitize=address

HEAD	=	minishell.h

CC		=	gcc

RM		=	-rm	-f

NAME	=	minishell

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
		$(CC) ${OBJS} ${P_OBJS} -Llibft -lft -lreadline \
		-L/usr/local/Cellar/readline/8.1/lib \
		-I/usr/local/Cellar/readline/8.1/include \
		-o ${NAME}

		#-L/Users/mehtel/.brew/Cellar/readline/8.1/lib \
		#-I/Users/mehtel/.brew/Cellar/readline/8.1/include \

#$(CC) ${OBJS} ${P_OBJS} -Llibft -lft -lreadline -ltermcap -o ${NAME}

all:	${NAME}

clean: $(SUBDIRS)
		${RM} ${OBJS} ${P_OBJS}

fclean: clean
		${RM} ${NAME}

re:     fclean	all

.PHONY:	re bonus all clean fclean $(SUBDIRS) $(TOPTARGETS)
