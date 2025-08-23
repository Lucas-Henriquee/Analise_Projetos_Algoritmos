# Compiler
CXX := g++

# Directories
SRC_DIR := src
INC_DIR := include
BUILD_DIR := build

# Source and header files
SRCS := $(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(filter-out main.cpp, $(SRCS)))
MAIN_OBJ := $(BUILD_DIR)/main.o
DEPS := $(wildcard $(INC_DIR)/*.hpp)

# Compiler flags
CXXFLAGS := -std=c++17 -Wall -Wextra -g -I$(INC_DIR)

TARGET := apa

# OS-specific commands
ifeq ($(OS),Windows_NT)
    MKDIR_CMD = @if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
    RM_CMD = @if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR) && if exist $(TARGET).exe del $(TARGET).exe
    EXEC_CMD = .\\$(TARGET)
else
    MKDIR_CMD = @mkdir -p $(BUILD_DIR)
    RM_CMD = @rm -rf $(BUILD_DIR) $(TARGET)
    EXEC_CMD = ./$(TARGET)
endif

.PHONY: all clean 

# Build and run everything
all: $(TARGET)
	chmod +x exec_all.sh

# Link objects into executable
$(TARGET): $(OBJS) $(MAIN_OBJ)
	@$(CXX) $(CXXFLAGS) $(OBJS) $(MAIN_OBJ) -o $(TARGET)

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	$(MKDIR_CMD)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: main.cpp $(DEPS)
	$(MKDIR_CMD)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	@$(RM_CMD)
	@chmod -x exec_all.sh
