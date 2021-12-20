SRCS            = main.c\
					utils/ft_strcmp.c\
					utils/ft_strdup.c\
					utils/lst.c\
					utils/split.c\
					utils/free.c\
					src/get_path.c\
					src/parse_line.c\
					src/pipe.c\
					src/exec.c\
					src/redirec.c\
					src/tokenize.c\
					src/signal.c\
					built_in/export.c\
					built_in/unset.c
					
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
		rm -f src/*.o
		rm -f built_in/*.o
		rm -f *.o

fclean:		clean
				${RM} ${NAME}

re:             clean all

.PHONY: all clean fclean re