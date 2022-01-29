# Compile settings
CXX	:= g++
CXXFLAGS := -g -std=c++11 -Wall

# Target executable
TARGET := raytracer

# Directories
SRC_DIRS := ./src
BUILD_DIR := ./build

# Files from directories
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# Build step: object files -> executable
$(BUILD_DIR)/$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(@) $(LDFLAGS)

# Build step: C++ files -> object files
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $(@))
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $(@) $(<) 

# Phony declarations
.PHONY: clean run

# Clean build directory
clean:
	rm -r $(BUILD_DIR)

# Run executable
run: $(BUILD_DIR)/$(TARGET)
	$(BUILD_DIR)/$(TARGET)
