# Compiler
CXX=gcc

# Compiler except optimization
CXX_E=gcc -O0

# Specify the "clean" target as a .PHONY target
.PHONY: clean all

# Compile static library
static:
	$(CXX_E) -c libcollatz.c
	ar rcs libcollatz.a libcollatz.o

# Compile shared library
shared:
	$(CXX_E) -fPIC -c libcollatz.c
	$(CXX_E) -shared libcollatz.o -o libcollatz.so

# First - with static library
first: main.c
	$(CXX_E) main.c libcollatz.a -o first

# Second - with shared library
second: main.c
	$(CXX_E) main.c -L. -lcollatz -Wl,-rpath=. -o second

# Third - with dynamic library
third: main2.c
	$(CXX_E) main2.c -o third -ldl

# Clear files
clean:
	rm -f libcollatz.a libcollatz.o libcollatz.so first second third

# Specify the "clean" target as a .PHONY target
.PHONY: clean
