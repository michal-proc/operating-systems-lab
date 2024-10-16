# Compiler
CXX=gcc

# Exercise 1 - calculate integral in separate processes
integral_processes: integral.c
	$(CXX) integral.c -o integral -lm

# Exercise 2 - calculate integral via two programmes
integral_two_programmes: sender_integral.c receiver_integral.c
	$(CXX) sender_integral.c -o sender_integral
	$(CXX) receiver_integral.c -o receiver_integral -lm

# Remove files
clean:
	rm -r integral

# Specify the "clean" target as a .PHONY target
.PHONY: clean
