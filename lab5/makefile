# Compiler
CXX=gcc

# Exercise 1 - handle SIGUSR1 in different ways
sigusr: sigusr.c
	$(CXX) sigusr.c -o sigusr

# Run with directory
sender_and_catcher: sender.c catcher.c
	$(CXX) sender.c -o sender
	$(CXX) catcher.c -o catcher

# Remove files
clean:
	rm -r sigusr sender catcher

# Specify the "clean" target as a .PHONY target
.PHONY: clean
