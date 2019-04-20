# Makefile for text dungeon

#*****************************************
# Variables to control Makefile operation


CXX = g++
CXXFLAGS = -Wall -g

#*****************************************
# Targets needed to bring the exe up to date

main: main.o room.o player.o
	$(CXX) $(CXXFLAGS) -o main main.o room.o player.o

# The main.o target can be written more simply

main.o: main.cpp room.hpp player.hpp
		$(CXX) $(CXXFLAGS) -c main.cpp

room.o: room.hpp

player.o: player.hpp
