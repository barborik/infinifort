CC = gcc

CP = cp
RM = rm -rf
MKDIR = mkdir

CFLAGS = -O2 -std=c99 -Wall -Wextra -Wpedantic
LFLAGS = -lSDL2main -lSDL2 -lSDL2_image -lm

SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))

TARGET = bin/infinifort

ifeq ($(OS),Windows_NT)
CP = cmd /C copy
RM = cmd /C rd /s /q
MKDIR = cmd /C mkdir

LIBS = -L lib/SDL2-2.30.8-x86_64-mingw32/lib/ -L lib/SDL2_image-2.8.2-x86_64-mingw32/lib/
INCLUDES = -I lib/SDL2-2.30.8-x86_64-mingw32/include/ -I lib/SDL2_image-2.8.2-x86_64-mingw32/include/
endif

all: init $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $^ -o $@ $(LIBS) $(LFLAGS)

obj/%.o: src/%.c
	$(CC) -c $< -o $@ $(INCLUDES) $(CFLAGS)

init:
ifeq (,$(wildcard obj))
	-$(MKDIR) obj
endif
ifeq (,$(wildcard bin))
	-$(MKDIR) bin
ifeq ($(OS),Windows_NT)
	-$(CP) lib\SDL2-2.30.8-x86_64-mingw32\bin\SDL2.dll bin
	-$(CP) lib\SDL2_image-2.8.2-x86_64-mingw32\bin\SDL2_image.dll bin
endif
endif

clean:
ifneq (,$(wildcard obj))
	-$(RM) obj
endif
ifneq (,$(wildcard bin))
	-$(RM) bin
endif