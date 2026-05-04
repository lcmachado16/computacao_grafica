CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Ajuste conforme sua instalação (Apple Silicon vs Intel)
INCLUDES = -I/opt/homebrew/include
LIBS = -L/opt/homebrew/lib -lglfw -lGLEW -framework OpenGL

SRC = main.cpp
OUT = app

all:
	$(CXX) $(SRC) $(CXXFLAGS) $(INCLUDES) $(LIBS) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)