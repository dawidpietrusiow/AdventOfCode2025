CXX = g++
CXXFLAGS = -std=c++17

.PHONY: all clean

# Get all currently existing days
DAYS := $(wildcard day*)

# Default target
all: $(DAYS:%=%/run)

# Compile code for each day
%/run: %/src.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Delete executables
clean:
	rm -f $(DAYS:%=%/run)
