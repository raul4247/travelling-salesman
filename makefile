CFLAGS = -O2
CC = g++

SOURCE_PATH = src/
BUILD_PATH = build/
OBJ_SUFIX = .o

TARGET = $(BUILD_PATH)TravelingSalesman

SRC = main Point Graph InputManager
_SRC = $(addprefix $(BUILD_PATH), $(addsuffix $(OBJ_SUFIX), $(SRC)))

all: $(_SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(_SRC)

$(BUILD_PATH)%.o: $(SOURCE_PATH)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	@echo "Cleaning up..."
	rm build/* inputs/*
