CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -g
TARGET = maze

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)
