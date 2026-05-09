# =========================
# Compiler
# =========================
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# =========================
# Diretórios
# =========================
SRC_DIR = src
INC_DIR = include

# Detecta SO
UNAME_S := $(shell uname -s)

# =========================
# Arquivos
# =========================
SRC = $(SRC_DIR)/main.cpp $(SRC_DIR)/glad.c

# =========================
# macOS
# =========================
ifeq ($(UNAME_S),Darwin)

	CXX = clang++

	# Remova esta linha se usar Intel
	CXXFLAGS += -arch arm64

	BIN_DIR = bin/macOS
	OUT = $(BIN_DIR)/main

	BREW_PREFIX = /opt/homebrew

	INCLUDES = \
		-I$(INC_DIR) \
		-I$(BREW_PREFIX)/include

	LIBS = \
		-L$(BREW_PREFIX)/lib \
		-lglfw \
		-framework OpenGL \
		-framework GLUT \
		-framework Cocoa \
		-framework IOKit \
		-framework CoreVideo

endif

# =========================
# Linux
# =========================
ifeq ($(UNAME_S),Linux)

	BIN_DIR = bin/Linux
	OUT = $(BIN_DIR)/main

	INCLUDES = -I$(INC_DIR)

	LIBS = \
		-lglfw \
		-lglut \
		-lGLU \
		-lGL \
		-ldl

endif

# =========================
# Build
# =========================
all: $(OUT)

$(OUT): $(SRC)
	mkdir -p $(BIN_DIR)
	$(CXX) $(SRC) $(CXXFLAGS) $(INCLUDES) $(LIBS) -o $(OUT)

# =========================
# Run
# =========================
run: all
	cd $(BIN_DIR) && ./main

# =========================
# Clean
# =========================
clean:
	rm -rf bin

.PHONY: all run clean