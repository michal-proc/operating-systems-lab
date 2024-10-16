# Compiler
CXX=gcc

# Create processes
processes: processes.c
	$(CXX) processes.c -o processes

# Run with directory
directory: directory.c
	$(CXX) directory.c -o directory

# Remove files
clean:
	rm -r processes directory

# Specify the "clean" target as a .PHONY target
.PHONY: clean
