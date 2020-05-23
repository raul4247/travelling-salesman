CFLAGS = -O2
CC = g++

SOURCE_PATH = src/
BUILD_PATH = build/
OBJ_SUFIX = .o

NAME = TravelingSalesman
TARGET = $(BUILD_PATH)$(NAME)

SRC = main Point Graph InputManager Utils TSPAlgorithms TSPResult
_SRC = $(addprefix $(BUILD_PATH), $(addsuffix $(OBJ_SUFIX), $(SRC)))

all: $(_SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(_SRC)
	@echo "$(NAME) has been built"

$(BUILD_PATH)%.o: $(SOURCE_PATH)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning up..."
	rm build/* inputs/*
