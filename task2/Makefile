CC = gcc
CFLAGS = -Wall -Wextra -pthread
SRC = src/main.c src/array_rw.c
INCLUDE = include
TARGET = lab7_task2

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -I$(INCLUDE) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
