NAME = philo_bonus

SRCS = $(shell find "." -name "*.c")

OBJS = $(SRCS:.c=.o)

CC = gcc

RM = rm -rf

CFLAGS = -Wall -Wextra -Werror  -pthread

all: ${NAME}

${NAME} : ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} $(OBJS)

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
