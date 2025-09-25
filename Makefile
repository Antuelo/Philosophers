NAME = philosophers
INCLUDE = Iincludes
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
MAKEFLAGS += --no-print-directory

SRCS := ./main.c $(shell find -name '*.c')
OBJS := $(SRCS:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS)
	@echo "PHILOSOPHERS compiled successfully :D"

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@$(MAKE) -C clean
	@$(RM) $(OBJS)
	@echo "🧹 PHILOSOPHERS files removed successfully!"

fclean: clean
	@$(MAKE) -C fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
