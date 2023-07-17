# Variables
CXX = g++
CXXFLAGS = -Wall -g

# Targets
all: server

server: src/main.cpp
	$(CXX) $(CXXFLAGS) -o server src/main.cpp

clean: 
	rm -f server
