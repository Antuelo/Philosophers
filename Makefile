NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
IFLAGS = -Iincludes
MAKEFLAGS += --no-print-directory

SRC_DIR:= src
OBJDIR := objets

SRCS := $(shell find src -type f -name '*.c')
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJDIR)/%.o)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "PHILOSOPHERS compiled successfully :D"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	@echo "🧹 PHILOSOPHERS files removed successfully!"

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
