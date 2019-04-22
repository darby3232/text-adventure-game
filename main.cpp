#include <iostream>
#include <fstream>
#include <vector>
#include "room.hpp"
#include "player.hpp"
#include <sstream>
#include <string>
#include<bits/stdc++.h> 


std::vector<Room> dungeon(50); 
Player *Player1 = new Player();
int currentRoomId = 1; 
bool justEnteredRoom = true;

bool fillDungeon(std::string fileName){

	std::filebuf fb; 
	if(fb.open(fileName, std::ios::in)){
		std::istream is(&fb); 
			
		//use getline here
		int currentRoom = 1; 
		std::string fileLine; 
		while(getline(is, fileLine)){
			std::stringstream ss;
		   	ss << fileLine;	
			std::string token; 
			std::vector<std::string> tokens; 
			
			while(getline(ss, token, '|')){
				tokens.push_back(token); 
			}
		
			dungeon[currentRoom].init(tokens[1], std::stoi(tokens[2]), std::stoi(tokens[3]), std::stoi(tokens[4]), std::stoi(tokens[5])); 
			
			currentRoom++;
		}	
		fb.close();
	}else{
		return false; 
	}
	return true; 
}


bool validateRooms(){
	//check that rooms match up with their opposite
	return true; 
}


bool roomMovement(std::string playerInput){

	int moveResult = 0; 
	std::string directionString; 

	if(playerInput.find("north") != std::string::npos){
		//check if we can move north
		moveResult = dungeon[currentRoomId].moveNorth();
		directionString = "north"; 		
	}else if(playerInput.find("south") != std::string::npos){
		moveResult = dungeon[currentRoomId].moveSouth();
		directionString = "south"; 
	}else if(playerInput.find("east") != std::string::npos){
		moveResult = dungeon[currentRoomId].moveEast();
		directionString = "east";
	}else if(playerInput.find("west") != std::string::npos){
		moveResult = dungeon[currentRoomId].moveWest();
		directionString = "west";
	}else{
		//else no movement speech
		return false;
	}
		
	if(moveResult < 0){
		std::cout << "It seems the " << directionString  << "ern way is locked." << std::endl;
	}else if(moveResult == 0){
		std::cout << "There is no way to go " << directionString << "." << std::endl;
	}else{
		std::cout << "Moved " << directionString << "." << std::endl;
		currentRoomId = moveResult; 
		justEnteredRoom = true;
	}
	return true;
}

bool processInput(){

	std::string playerInput;
    	std::getline(std::cin, playerInput); 

	if(playerInput == "quit" || playerInput == "exit"){
		return false; 
	}

	if(roomMovement(playerInput)){
		return true;
	} 

	std::cout << playerInput << " not understood." << std::endl;

	return true;
}

int main(){
	std::cout <<"Please Enter a Name"<<std::endl;
	std::string name;
	std::cin>>name;

	std::vector<std::string> inventory(50);

	Player1->init(name, inventory);
	Player1->setName(name);
	std::cout << "Hello, "<<Player1->getName() << std::endl;

	if(!fillDungeon("castle.dng")){
		std::cerr << "castle.dng could not be loaded" << std::endl;
		return 1; 
	}		

	std::string playerInput; 

	do{
		if(justEnteredRoom){
			std::cout << dungeon[currentRoomId].getRoomDescription() << std::endl; 
			justEnteredRoom = false; 
		}
	}while(processInput());

	std::cout << "See you next time...!" << std::endl;

	return 0; 
}
