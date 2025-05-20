NAME = gestatt
SRC_DIR = src
TESTS_DIR = tests
BIN_DIR = bin


SOURCE = $(SRC_DIR)/activity.c $(SRC_DIR)/activities_container_support_list.c $(SRC_DIR)/activities_container.c $(SRC_DIR)/utils.c $(SRC_DIR)/main.c
SOURCE_TESTS = $(SRC_DIR)/activity.c $(SRC_DIR)/activities_container_support_list.c $(SRC_DIR)/activities_container.c $(SRC_DIR)/utils.c $(SRC_DIR)/test_main.c
CC = gcc

all: $(NAME)
	
$(NAME): dirstructure
	$(CC) $(SOURCE) -o $(BIN_DIR)/$(NAME)

dirstructure:
	mkdir -p $(BIN_DIR)

clean:
	rm -f $(BIN_DIR)/$(NAME)
	rm -f $(TESTS_DIR)/$(NAME)_test
	
test:
	$(CC) $(SOURCE_TESTS) -o $(TESTS_DIR)/$(NAME)_test
	cd $(TESTS_DIR); ./$(NAME)_test