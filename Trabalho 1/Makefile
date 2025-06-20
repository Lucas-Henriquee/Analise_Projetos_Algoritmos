# Compiler
CXX := g++

# Directories
SRC_DIR := source
INC_DIR := include
BUILD_DIR := build

# Source and header files
SRCS := $(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(filter-out main.cpp, $(SRCS)))
MAIN_OBJ := $(BUILD_DIR)/main.o
DEPS := $(wildcard $(INC_DIR)/*.hpp)

# Compiler flags
CXXFLAGS := -std=c++17 -Wall -Wextra -g -I$(INC_DIR)

# Executable name
TARGET := apa

# Python script path
PYTHON_SCRIPT := analysis/plot_results.py

# OS-specific commands
ifeq ($(OS),Windows_NT)
    MKDIR_CMD = @if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
    RM_CMD = @if exist $(BUILD_DIR) rmdir /S /Q $(BUILD_DIR) && if exist $(TARGET).exe del $(TARGET).exe
    PYTHON_CHECK = where python >nul 2>&1
    PYTHON_RUN = python
    EXEC_CMD = .\\$(TARGET)
else
    MKDIR_CMD = @mkdir -p $(BUILD_DIR)
    RM_CMD = @rm -rf $(BUILD_DIR) $(TARGET)
    PYTHON_CHECK = command -v python3 > /dev/null
    PYTHON_RUN = $(shell which python3)
    EXEC_CMD = ./$(TARGET)
endif

.PHONY: all clean run build_only check_python ask_plot check_python_modules run_python_plot

# Build and run everything
all: build_only run ask_plot

# Only compile
build_only: $(TARGET)

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

# Run C++ executable
run:
	@echo "Running..."
	@$(EXEC_CMD)

# Ask user if they want to run Python plot, then check Python and modules
ask_plot:
	@echo -n "Do you want to plot the results with Python? (y/n): "; \
	read answer; \
	if [ "$$answer" = "y" ] || [ "$$answer" = "Y" ]; then \
		$(MAKE) --no-print-directory check_python; \
		$(MAKE) --no-print-directory check_python_modules; \
		if [ $$? -eq 0 ]; then \
			$(MAKE) --no-print-directory run_python_plot; \
		else \
			echo "Skipping plot due to missing Python libraries or user choice. Execution finished."; \
		fi; \
	else \
		echo "Skipping plot. Execution finished."; \
	fi

# Check Python installation
check_python:
	@echo "Checking if Python is installed..."
	@$(PYTHON_CHECK) || (echo "Python is not installed. Please install it to use the plotting features." && exit 1)

# Check for required Python modules and optionally install them
check_python_modules:
	@echo "Checking for required Python modules..."
ifeq ($(OS),Windows_NT)
	@$(PYTHON_RUN) -c "import pandas, matplotlib.pyplot, seaborn" 2>nul || ( \
		echo ""; \
		echo "--- Warning ---"; \
		echo "The following Python libraries are required to generate plots:"; \
		echo "  - pandas"; \
		echo "  - matplotlib"; \
		echo "  - seaborn"; \
		echo ""; \
		echo "You can install them by running the command:"; \
		echo "    pip install pandas matplotlib seaborn"; \
		echo ""; \
		echo "Plotting will be skipped this time. If you wish to use the plots in the future, please install these libraries."; \
		exit 1 \
	)
else
	@missing_modules=""; \
	for module in pandas matplotlib seaborn; do \
		$(PYTHON_RUN) -c "import $$module" >/dev/null 2>&1 || missing_modules="$$missing_modules $$module"; \
	done; \
	if [ "$$missing_modules" != "" ]; then \
		echo ""; \
		echo "--- Warning ---"; \
		echo "The following Python libraries are required to generate plots:"; \
		for module in $$missing_modules; do echo "  - $$module"; done; \
		echo ""; \
		echo "To install all required modules, run:"; \
		echo "  pip install$$missing_modules"; \
		echo ""; \
		echo "After installing, please run 'make' again."; \
		exit 1; \
	fi; \
	true
endif

# Run Python plot script
run_python_plot:
	@echo "Generating plot with Python..."
	@$(PYTHON_RUN) $(PYTHON_SCRIPT)

# Clean build artifacts
clean:
	@$(RM_CMD)
