NAME	= test

OBJS		=	$(SRCS:.c=.o)
SRC_DIR		=	.
HEADERS		=	./mini_parser.h
#INC_DIR 	=	./include
#LINK		=	-I$(INC_DIR)
SRCS		=	./mini_parser.c \
				./get_next_line.c ./get_next_line_utils.c ./utils.c ./error_out.c \
				./ft_list_utils.c ./env_func.c

CFLAGS	= #-Wall -Wextra -Werror
RM		= rm -f
CC		= gcc

all:		$(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	${CC} $(CFLAGS) -c $< -o $@

${NAME}: 	${OBJS}
	${CC} -o ${NAME} ${OBJS}

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re