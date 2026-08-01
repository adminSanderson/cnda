# =====================
# OS
# =====================
ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
else
    DETECTED_OS := $(shell uname -s)
endif

CC = gcc
CFLAGS = -Wall -Wextra -O3 -Iinclude
LDFLAGS =

# commands for OS
ifeq ($(DETECTED_OS),Windows)
    TARGET = cnda.exe
    LIB_NAME = libcnda.a
    RM = del /Q /S
    MKDIR = if not exist "$(subst /,\,$1)" mkdir "$(subst /,\,$1)"
    FixPath = $(subst /,\,$1)
else
    TARGET = cnda
    LIB_NAME = libcnda.a
    RM = rm -rf
    MKDIR = mkdir -p $1
    FixPath = $1
endif

ifeq ($(DETECTED_OS),Darwin)
    CFLAGS += -march=native
else ifeq ($(DETECTED_OS),Linux)
    CFLAGS += -march=native -flto
endif

# =====================
# FILES
# =====================
SRC = $(wildcard src/nda/*.c )
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))

# =====================
# LAWS
# =====================
.PHONY: all clean lib test

all: lib

build/%.o: src/%.c
	@$(call MKDIR,$(dir $@))
	$(CC) $(CFLAGS) -c $< -o $@

lib: $(OBJ)
	ar rcs $(LIB_NAME) $(OBJ)

TEST_SRC = $(wildcard tests/test_*.c)
TEST_BIN = $(patsubst tests/%.c, build/tests/%, $(TEST_SRC))

test: lib
	@$(call MKDIR,build/tests)
	@for src in $(TEST_SRC); do \
		name=$$(basename $$src .c); \
		echo "== $$name =="; \
		$(CC) $(CFLAGS) -Itests $$src -L. -lcnda -lm -o build/tests/$$name $(LDFLAGS) && ./build/tests/$$name || exit 1; \
	done

clean:
	$(RM) build $(LIB_NAME)
