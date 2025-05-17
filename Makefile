NAME = gestatt
SRC_DIR = src
TESTS_DIR = tests #todo
BIN_DIR = bin


SOURCE = $(SRC_DIR)/activity.c $(SRC_DIR)/activities_container.c $(SRC_DIR)/utils.c $(SRC_DIR)/main.c
CC = gcc

all: $(NAME)
	
$(NAME): dirstructure
	$(CC) $(SOURCE) -o $(BIN_DIR)/$(NAME)

dirstructure:
	mkdir -p $(BIN_DIR)

clean:
	rm -f $(BIN_DIR)/$(NAME)