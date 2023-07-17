# Variables
CXX = g++
CXXFLAGS = -Wall -g

# Targets
all: server

server: src/main.cpp
	$(CXX) $(CXXFLAGS) -o server src/main.cpp

stop:
	perl stop_server.pl

clean: 
	rm -f server
