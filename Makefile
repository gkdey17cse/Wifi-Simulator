# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Directories
INCLUDE_DIR = include
SRC_DIR = src
BUILD_DIR = build

# Target executable
TARGET = $(BUILD_DIR)/WiFiSimulator

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Default target
all: $(TARGET)

# Build the target executable
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Debug build
debug: CXXFLAGS += -g
debug: clean all

# Optimized build
optimized: CXXFLAGS += -O3
optimized: clean all

# Phony targets
.PHONY: all clean debug optimized
