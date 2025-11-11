CC = gcc
CFLAGS = -Wall -Wextra -pthread
SRC = src/main.c src/integral.c
INCLUDE = include
TARGET = lab7_task1

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -I$(INCLUDE) $(SRC) -lm -o $(TARGET)

clean:
	rm -f $(TARGET)
