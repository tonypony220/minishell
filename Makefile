dir		=   .

SRCS	=	fork.c multalloc.c find_path.c builtins.c dict_func.c environ.c exiting.c term.c main.c

PARSER_DIR = mini_shell
PARSER		=	PARSER_DIR/mini_parser.c \
				PARSER_DIR/get_next_line.c PARSER_DIR/get_next_line_utils.c \
				PARSER_DIR/utils.c PARSER_DIR/error_out.c \
				PARSER_DIR/ft_list_utils.c PARSER_DIR/env_func.c \
				PARSER_DIR/parsers.c PARSER_DIR/mini_exec.c PARSER_DIR/command.c

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
