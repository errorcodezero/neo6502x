SRC_DIR = src
BUILD_DIR = build
EXE = neo6502x

SRC = main.c vm.c utils.c status.c bool_ops.c shift_ops.c load_ops.c
OBJ = $(SRC:%.c=$(BUILD_DIR)/%.o)

CFLAGS += -std=c23 -Wall -Wextra -Werror -pedantic
# CC = gcc

all: debug

release: setup
release: CFLAGS += -O3 -DNDEBUG
release: $(BUILD_DIR)/$(EXE)

debug: setup
debug: CFLAGS += -g
debug: $(BUILD_DIR)/$(EXE)

debug-memory: setup
debug-memory: CFLAGS += -g -fsanitize=address,undefined
debug-memory: $(BUILD_DIR)/$(EXE)

.PHONY: all debug release clean setup

setup:
	mkdir -p build/

clean:
	rm -rf build

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
