## ============================= NAMES ========================================== ##

NAME = philo

## ============================= FLAGS ========================================== ##

CC = gcc

C_FLAGS = -Wall -Wextra -Werror -g -lpthread

## ============================ DIRECTORIES ==================================== ##

INC_DIR = include

SRC_DIR = src

BIN_DIR = bin

OBJ_DIR = obj

## ============================ SOURCES ======================================= ##

SRC = $(SRC_DIR)/philo.c $(SRC_DIR)/utils.c $(SRC_DIR)/mutex_access.c $(SRC_DIR)/free_exit.c \
	$(SRC_DIR)/utils_2.c $(SRC_DIR)/init.c $(SRC_DIR)/simulation.c $(SRC_DIR)/mutex_handle.c \
	$(SRC_DIR)/status.c $(SRC_DIR)/monitoring.c $(SRC_DIR)/single_philo.c $(SRC_DIR)/sim_utils.c

TARGET = philo

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# default rule

all: $(BIN_DIR)/$(NAME)

#linking

$(BIN_DIR)/$(NAME): $(OBJ)
	@mkdir -p $(BIN_DIR)
	$(CC) $(C_FLAGS) -I$(INC_DIR) -o $@ $^

#compiling

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(C_FLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(BIN_DIR)

1philo:
	./$(BIN_DIR)/$(TARGET) 1 800 200 200

2philo:
	./$(BIN_DIR)/$(TARGET) 2 800 200 200

die2philo:
	./$(BIN_DIR)/$(TARGET) 2 310 200 100

2full:
	./$(BIN_DIR)/$(TARGET) 2 800 200 200 7 > full.txt && cat full.txt | grep eating > eat_sum.txt
	cat eat_sum.txt | grep eating
	cat eat_sum.txt | grep eating | wc -l


test:
	./$(BIN_DIR)/$(TARGET) 6 800 200 200 5 > file.txt
	cat file.txt | grep eating
	cat file.txt | grep eating | wc -l

valgrind:
	valgrind --leak-check=full ./$(BIN_DIR)/$(TARGET) 5 800 200 200 7 > file2.txt && cat file2.txt | grep "eating" > eat_sum.txt && cat eat_sum.txt
	cat eat_sum.txt | wc -l

re: fclean all

.PHONY: all clean fclean re
