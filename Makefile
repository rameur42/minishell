SRCS            = main.c\
					utils/ft_strcmp.c\
					utils/ft_strdup.c\
					utils/lst.c\
					utils/split.c\
					utils/free.c\
					utils/substr.c\
					utils/atoi.c\
					utils/itoa.c\
					src/get_path.c\
					src/parse_line.c\
					src/pipe.c\
					src/exec.c\
					src/redirec.c\
					src/tokenize.c\
					src/signal.c\
					src/env_var.c\
					src/env.c\
					src/init_redirec.c\
					src/init_redir2.c\
					src/lst_token.c\
					src/count.c\
					src/parse_token.c\
					built_in/export.c\
					built_in/export2.c\
					built_in/export3.c\
					built_in/export4.c\
					built_in/export5.c\
					built_in/unset.c\
					built_in/built_in.c\
					built_in/built_in2.c\
					built_in/built_in3.c\
					built_in/built_in_utils.c
					
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