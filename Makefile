# Simple Makefile for Windows + raylib + C++ (VS Code)
# Change this if your raylib folder is somewhere else
RAYLIB_PATH = C:/raylib/raylib

# Your project name (output exe)
PROJECT_NAME = main

# Source and object directories
SRC_DIR = src
OBJ_DIR = obj

# All .cpp files in src/
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) #automatically finds all .cpp files in src/ (e.g., main.cpp, dice.cpp, sprite.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o) # turns those into .o files in the obj/ folder

# Compiler and flags
CC = g++
CXXFLAGS = -I$(RAYLIB_PATH)/src -std=c++14 -Wall
LDFLAGS = -L$(RAYLIB_PATH)/src
LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm -static

# Build mode: DEBUG or RELEASE
BUILD_MODE := DEBUG

ifeq ($(BUILD_MODE),DEBUG)
	CXXFLAGS += -g -O0
	OUTPUT_NAME = $(PROJECT_NAME).exe
else
	CXXFLAGS += -O2 -s
	OUTPUT_NAME = $(PROJECT_NAME)_release.exe
endif

$(info *** BUILD_MODE = $(BUILD_MODE) ***)
$(info *** OUTPUT_NAME = $(OUTPUT_NAME) ***)
$(info *** CXXFLAGS = $(CXXFLAGS) ***)

# --------------------- TARGETS ---------------------

# Default target
all: $(OUTPUT_NAME)

# Link object files into final executable
$(OUTPUT_NAME): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(OUTPUT_NAME) $(LDFLAGS) $(LDLIBS)
	@echo "Build complete: $(OUTPUT_NAME)"

# Compile .cpp → .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR) #"For every .cpp file in src/, compile it into a .o file in obj/"
	$(CC) $(CXXFLAGS) -c $< -o $@ 

# Create obj folder if it doesn't exist
$(OBJ_DIR):
	mkdir $(OBJ_DIR)

# Clean build files
clean:
	rmdir /s /q $(OBJ_DIR) 2>nul || true
	del *.exe 2>nul || true
	@echo "Clean done"

# Shortcuts:    (make run)/(make run-release)
# Run the game (debug version if exists)
run: $(PROJECT_NAME).exe
	./$(PROJECT_NAME).exe

# Run release version
run-release: $(PROJECT_NAME)_release.exe
	./$(PROJECT_NAME)_release.exe

.PHONY: all clean run run-release # Tells make these (shortcuts) aren't real files (so it always runs them)