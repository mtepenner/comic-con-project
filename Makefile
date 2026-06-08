# Variables
CXX = g++
CXXFLAGS = -Wall -std=c++11

# The output executable
TARGET = backend/backend.exe

# Grab ALL .cpp files in the backend directory automatically
SRC = $(wildcard backend/*.cpp)

PYTHON = python3 

# Default target: builds the backend and runs the frontend
all: build run

# Compile the C++ backend
build:
	@echo "💥 Compiling C++ Backend..."
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)
	@echo "✅ Backend compiled successfully!"

# Run the Python frontend
run:
	@echo "🚀 Launching Comic-Con Terminal..."
	$(PYTHON) frontend/main.py

# Clean up generated files
clean:
	@echo "🧹 Cleaning up workspace..."
	rm -f $(TARGET) comicon_data.txt users.json bank_config.json
	@echo "✨ Workspace clean!"
