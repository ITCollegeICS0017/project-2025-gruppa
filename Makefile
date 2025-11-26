CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 -Isrc
LDFLAGS :=

SRC_DIR := src
BUILD_DIR := build

# Find all .cpp files
SRCS := $(shell find $(SRC_DIR) -name '*.cpp')

# Convert src/path/file.cpp to build/path/file.o
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Targets for Linux and Windows
TARGET_LINUX := $(BUILD_DIR)/store
TARGET_WINDOWS := $(BUILD_DIR)/store.exe

# Default target builds both
all: $(TARGET_LINUX) $(TARGET_WINDOWS)

# Linux executable
$(TARGET_LINUX): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Windows executable
$(TARGET_WINDOWS): $(OBJS)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Compile .cpp to .o ensuring directories exist
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean everything
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
