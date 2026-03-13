//  file:        Makefile
//  context:     build automation
//  description: compiles copy project with object files and linking

CC        = gcc
CFLAGS    = -Wall -Wextra -std=c99 -I. -Ifileops -Ierrors -Istats
BIN_DIR   = bin
BUILD_DIR = build
TARGET    = $(BIN_DIR)/copy
SOURCES   = main.c fileops/fileops.c fileops/copy.c fileops/tab_handler.c errors/errors.c stats/stats.c
OBJECTS   = $(addprefix $(BUILD_DIR)/,$(SOURCES:.c=.o))

all: $(BIN_DIR) $(BUILD_DIR) $(TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild
