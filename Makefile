# write the make file with the following targets main.cpp

# Target: main.cpp
# Compile the main.cpp file
# Dependencies: main.cpp
# Command: g++ -o main main.cpp
main: main.cpp
	g++ -o main main.cpp

# Target: clean
# Remove the main executable
# Dependencies: main
# Command: rm main
clean:
	rm main

# Target: run
# Run the main executable
# Dependencies: main
# Command: ./main
run: main
	./main