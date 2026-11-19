NAME = codexion

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
INCLUDES = -Iinclude

SRC = src/main.c \
	src/parser.c \
	src/init.c \
	src/simulation.c \
	src/coder.c \
	src/scheduler.c \
	src/priority_queue.c \
	src/queue_init.c \
	src/dongles.c \
	src/monitor.c \
	src/logger.c \
	src/time_utils.c \
	src/cleanup.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c include/codexion.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re