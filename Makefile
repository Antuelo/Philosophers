NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
IFLAGS = -Iincludes
MAKEFLAGS += --no-print-directory

SRCS := $(shell find src -type f -name '*.c')
OBJS := $(SRCS:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "PHILOSOPHERS compiled successfully :D"

%.o: %.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	@echo "🧹 PHILOSOPHERS files removed successfully!"

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
