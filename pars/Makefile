NAME	= test

#TEST	= env

OBJS		=	$(SRCS:.c=.o)
SRC_DIR		=	.
HEADERS		=	./mini_parser.h
#INC_DIR 	=	./include
#LINK		=	-I$(INC_DIR)
SRCS		=	./mini_parser.c \
				./get_next_line.c ./get_next_line_utils.c ./utils.c ./error_out.c \
				./ft_list_utils.c ./env_func.c ./parsers.c ./mini_exec.c ./command.c

CFLAGS	= #-Wall -Wextra -Werror
RM		= rm -f
CC		= gcc

all:		$(NAME)

test:		$(TEST)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	${CC} $(CFLAGS) -c $< -o $@

${NAME}: 	${OBJS}
	${CC} -o ${NAME} -lreadline ${OBJS}

#${TEST}: 	${OBJS}
#	${CC} -o ${TEST} ${OBJS}

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
