CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic 
SDL_CFLAGS = -I/usr/headers/SDL2 -D_REENTRANT
LDFLAGS = -lSDL2 -lSDL2_image -lm

SRCDIR = src
INCDIR = headers
OBJDIR = obj

SOURCES = $(wildcard $(SRCDIR)/*.c)

OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

TARGET = maze_runner

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) -c $< -o $@ $(CFLAGS) $(SDL_CFLAGS) -I$(INCDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -f $(OBJDIR)/*.o $(TARGET)

.PHONY: all clean

