CC = gcc
CFLAGS = -W -Wall
TARGET = snake
DTARGET = snake_debug
OBJECTS = snake.o user.o manager.o game.o
all : $(TARGET)
$(TARGET) : $(OBJECTS)
		$(CC) $(CFLAGS) -o $@ $^
$(DTARGET) : $(OBJECTS)
		$(CC) $(CFLAGS) -DDEBUG -o $@ $^
clean:
		rm *.o snake
