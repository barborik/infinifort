CC = gcc

RM = rm -rf
MKDIR = mkdir

CFLAGS = -O2 -std=c99 -Wall -Wextra -Wpedantic
LFLAGS = -lSDL2main -lSDL2 -lm

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

TARGET = bin/infinifort

ifeq ($(OS),Windows_NT)
RM = cmd /C rd /s /q
MKDIR = cmd /C mkdir

LIBS = -Llib/SDL2-2.30.8-x86_64-mingw32/lib/
INCLUDES = -Ilib/SDL2-2.30.8-x86_64-mingw32/include/
endif

all: init $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $^ -o $@ $(LIBS) $(LFLAGS)

obj/%.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

init:
ifeq (,$(wildcard obj))
	-$(MKDIR) obj
endif
ifeq (,$(wildcard bin))
	-$(MKDIR) bin
endif

clean:
ifneq (,$(wildcard obj))
	-$(RM) obj
endif
ifneq (,$(wildcard bin))
	-$(RM) bin
endif