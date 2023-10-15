CC = g++
SRC_DIR = src
BIN_DIR = bin
EXECUTABLE = program
CFLAGS = -WALL


SOURCER = $(wildcard $(SRC_DIR)/*.cpp)

all: 
	@$(CC) -o $(BIN_DIR)/$(EXECUTABLE) $(SOURCER)

run:
	./$(BIN_DIR)/$(EXECUTABLE)

clean:
	@rm -f $(BIN_DIR)/$(EXECUTABLE)	

