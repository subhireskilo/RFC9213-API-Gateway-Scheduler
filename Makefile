CC = gcc
CFLAGS = -Wall -Wextra -g

OBJ = main.o request.o rfc_parser.o min_heap.o
TARGET = gateway

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)