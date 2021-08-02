SRCS            = main.c\
					utils/ft_strcmp.c\
					utils/ft_strdup.c\
					utils/lst.c\

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
		rm -f utils/*.o
		rm -f *.o

fclean:		clean
				${RM} ${NAME}

re:             clean all

.PHONY: all clean fclean re