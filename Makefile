CC = gcc
CFLAGS = -W -Wall
TARGET = snake
DTARGET = snake_debug
OBJECTS = snake.c game.o manager.o user.o
all : $(TARGET)
$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^
$(DTARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -DDEBUG -o $@ $^
clean:
	rm *.o *.exe