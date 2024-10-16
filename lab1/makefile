# Compiler
CXX=gcc

# Compiler flags
CFLAGS=-Wall -Wextra -pedantic

# Target: all (builds all targets)
all: countdown

# Target: countdown (builds countdown program)
countdown: countdown.c
	$(CXX) $(CFLAGS) -o countdown countdown.c

# Target: clean (cleans project)
clean:
	rm -f countdown

# Specify the "clean" target as a .PHONY target
.PHONY: clean