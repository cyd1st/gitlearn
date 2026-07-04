# Makefile for compiling cpp files in the current directory
# Each cpp file will be compiled to an executable in the out directory
# with the same name as the cpp file (without the .cpp extension)

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -O2 -pthread

# Find all cpp files in the current directory
SRCS := $(wildcard *.cpp)
# Generate target executable names by replacing .cpp extension with nothing
TARGETS := $(SRCS:.cpp=)
# Full paths for executables in out directory
OUT_TARGETS := $(addprefix out/, $(TARGETS))

# Default target
all: $(OUT_TARGETS)

# Create out directory if it doesn't exist
out:
	mkdir -p out

# Rule for compiling each cpp file to its corresponding executable in out directory
out/%: %.cpp | out
	$(CXX) $(CXXFLAGS) $< -o $@

# Clean target to remove all executables in out directory
clean:
	rm -rf out

# Phony targets
.PHONY: all clean out