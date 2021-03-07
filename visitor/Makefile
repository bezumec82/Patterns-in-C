SOURCES = src/*.c \
          src/*.h

CC = gcc
CFLAGS = -g -Wall -lm
# No fancy extensions here!
CFLAGS += -Wpedantic

TARGET = visitor.out

libabstract.a : lib/visitor.o lib/object.o
	ar rcs $@ $^
	ranlib $@

tags:
	rm -rf ./tags
	ctags -R .

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^ libabstract.a -Ilib

all: libabstract.a $(TARGET)

clean:
	rm -rf ./*.o ./*.out ./tags ./*.a

.PHONY: clean tags
