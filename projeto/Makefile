CC = gcc
CFLAGS = -Wall -Wextra
TARGET = damas
SRCS = main.c jogo.c ia.c arquivo.c utils.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
    $(CC) $(OBJS) -o $(TARGET)

%.o: %.c damas.h
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    del /F /Q $(OBJS) $(TARGET).exe

.PHONY: clean