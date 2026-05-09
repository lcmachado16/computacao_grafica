CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -arch arm64

# Diretórios
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin/macOS

# Arquivos
SRC = $(SRC_DIR)/main.cpp $(SRC_DIR)/glad.c
OUT = $(BIN_DIR)/main

# Homebrew (Apple Silicon)
BREW_PREFIX = /opt/homebrew

# Includes
INCLUDES = -I$(INC_DIR) -I$(BREW_PREFIX)/include

# Libs (macOS + GLFW)
LIBS = -L$(BREW_PREFIX)/lib -lglfw -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

# Regra padrão
all: $(OUT)

# Build
$(OUT): $(SRC)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(SRC) $(INCLUDES) $(LIBS) -o $(OUT)

# Executar
run: all
	cd $(BIN_DIR) && ./main

# Limpar
clean:
	rm -rf $(BIN_DIR)

.PHONY: all run clean