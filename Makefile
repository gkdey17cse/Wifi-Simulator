# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Directories
INCLUDE_DIR = include
SRC_DIR = src
BUILD_DIR = build

# Target executables
DEBUG_TARGET = $(BUILD_DIR)/WiFiSimulator_debug
OPTIMIZED_TARGET = $(BUILD_DIR)/WiFiSimulator_opt

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Default target: Build both debug and optimized binaries
all: $(DEBUG_TARGET) $(OPTIMIZED_TARGET)

# Build the optimized binary
$(OPTIMIZED_TARGET): $(OBJ_FILES)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -O3 $^ -o $@

# Build the debug binary
$(DEBUG_TARGET): $(OBJ_FILES)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -g $^ -o $@

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)

# Phony targets
.PHONY: all clean
