#
#  Copyright 2015 Wahankh <dev@wahankh.co.uk>
#

TARGET=wepu
CC=gcc -std=c99
CFLAGS=-Wall -I. `pkg-config --cflags --libs glib-2.0 gio-2.0`

SRC:=$(wildcard src/*.c)
OBJ:=$(SRC:src/%.c=obj/%.o)

DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CFLAGS+=-DDEBUG -g
else
	CFLAGS+=-DNDEBUG
endif

$(TARGET): $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS)
	
$(OBJ): obj/%.o: src/%.c
	mkdir -p obj
	$(CC) -c $< -o $@ $(CFLAGS)
	
.PHONY: clean
clean:
	rm -Rf obj $(TARGET)
