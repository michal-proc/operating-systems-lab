# Compiler
CXX=gcc

# Flags
CXX_FLAGS=-Wall -pthread

# Build all
all: server client

# Server
server: server.c
	$(CXX) $(CXX_FLAGS) server.c -o server

# Client
client: client.c
	$(CXX) $(CXX_FLAGS) client.c -o client

# Remove files
clean:
	rm -f server client

# Specify the "clean" target as a .PHONY target
.PHONY: clean
