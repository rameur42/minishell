SRCS            = main.c\

CC              = clang
CFLAGS          = -g -Wall -Wextra -Werror -I ./includes
NAME            = minishell

OBJS            = ${SRCS:.c=.o}

all:            $(NAME)

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	$(OBJS)
					${CC} -lreadline ${CFLAGS} ${OBJS} -o ${NAME}

clean:
		rm -f src/*.o
		rm -f op/*.o
		rm -f *.o

fclean:		clean
				${RM} ${NAME}

re:             clean all

.PHONY: all clean fclean re