SOURCES = *.c \
          *.h

CC = gcc
CFLAGS = -g -Wall
# No fancy extensions here!
CFLAGS += -Wpedantic

TARGET = template.out

tags:
	rm -rf ./tags
	ctags -R . --tag-relative=yes

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

all: $(TARGET)

clean:
	rm -rf ./*.o ./*.out ./tags ./*.a

.PHONY: clean tags
