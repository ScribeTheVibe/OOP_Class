CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
TARGET   := studentai
SRCDIR   := .
SOURCES  := main.cpp Functions.cpp Names.cpp
OBJECTS  := $(SOURCES:.cpp=.o)

# ── Default target ────────────────────────────────────────────────────────────
all: output $(TARGET)

# ── Link ──────────────────────────────────────────────────────────────────────
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# ── Compile each .cpp ─────────────────────────────────────────────────────────
%.o: %.cpp Headers.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# ── Create output directory if it doesn't exist ───────────────────────────────
output:
	mkdir -p output

# ── Run the program ───────────────────────────────────────────────────────────
run: all
	./$(TARGET)

# ── Remove build artifacts ────────────────────────────────────────────────────
clean:
	rm -f $(OBJECTS) $(TARGET)

# ── Remove build artifacts AND generated output files ─────────────────────────
cleanall: clean
	rm -rf output

.PHONY: all run clean cleanall output
