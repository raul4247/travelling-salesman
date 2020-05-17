CFLAGS = -O2
CC = g++

TARGET = build/TravelingSalesman

all: main Point Graph InputManager
	$(CC) $(CFLAGS) -o $(TARGET) build/main.o build/Point.o build/Graph.o build/InputManager.o

main: src/main.cpp src/Point.cpp src/Graph.cpp
	$(CC) $(CFLAGS) -c src/main.cpp -o build/main.o

Point: src/Point.cpp
	$(CC) $(CFLAGS) -c src/Point.cpp -o build/Point.o 

Graph: src/Graph.cpp
	$(CC) $(CFLAGS) -c src/Graph.cpp -o build/Graph.o 

InputManager: src/InputManager.cpp
	$(CC) $(CFLAGS) -c src/InputManager.cpp -o build/InputManager.o 

clean:
	@echo "Cleaning up..."
	rm build/* inputs/*
