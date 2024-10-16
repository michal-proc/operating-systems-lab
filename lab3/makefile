# Compiler
CXX=gcc

# Reverse files - two variants
reverse: reverse_byte.c reverse_block.c
	$(CXX) reverse_byte.c -o reverse_byte
	$(CXX) reverse_block.c -o reverse_block

# Show directory
directory: directory.c
	$(CXX) directory.c -o directory

# Remove files
clean:
	rm -r reverse_byte reverse_block directory

# Specify the "clean" target as a .PHONY target
.PHONY: clean
