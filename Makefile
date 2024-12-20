CC = gcc
CFLAGS += -Wall -Wextra -g -std=c11
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
TARGET = prog

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

