# Compiler
CXX=gcc

# Printer - System
system: system.c
	$(CXX) system.c -o system -lrt -lpthread

# User - Client
client: client.c
	$(CXX) client.c -o client -lrt -lpthread

# Remove files
clean:
	rm -r system client

# Specify the "clean" target as a .PHONY target
.PHONY: clean
