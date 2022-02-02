# Compile settings
CXX := g++

# Target executable
TARGET := raytracer

# Directories
SRC_DIRS := ./src
INC_DIRS := ./include
BUILD_DIR := ./build
INPUT_DIR := ./input
OUTPUT_DIR := ./output

# Files from directories
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp')
INCS := $(shell find $(INC_DIRS) -type d)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# Flags
CXXFLAGS := -g -std=c++11 -Wall
INC_FLAGS := $(addprefix -I,$(INCS))

# Build step: object files -> executable
$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(@) $(LDFLAGS)

# Build step: C++ files -> object files
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $(@))
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $(@) $(<) 

# Phony declarations
.PHONY: clean clean-all run

# Clean build directory
clean:
	rm -r $(BUILD_DIR)

# Clean build directory and output directory
clean-all:
	rm -r $(BUILD_DIR)
	rm -r $(OUTPUT_DIR)

# Run executable
run: $(BUILD_DIR)/$(TARGET)
	$(BUILD_DIR)/$(TARGET) input/input.txt
