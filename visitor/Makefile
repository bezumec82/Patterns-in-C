CC = gcc

CFLAGS = -g -Wall

SOURCES = *.c \

TARGET = visitor.out

INCLUDE = *.h

tags:
	ctags -R .


all: $(TARGET)
	gcc $(CFLAGS) $(SOURCES) $(INCLUDE) -o $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm *.o *.out
