/*
  file:        Makefile
  context:     build automation
  description: compiles copy project with object files and linking
*/

CC       = gcc
CFLAGS   = -Wall -Wextra -std=c99
TARGET   = copy
SOURCES  = main.c copy.c fileops.c errors.c stats.c
OBJECTS  = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild
