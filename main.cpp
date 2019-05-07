#include <iostream>
#include <fstream>
#include <vector>
#include "room.hpp"
#include "player.hpp"
#include "item.hpp"
#include <sstream>
#include <string>
#include<bits/stdc++.h> 

std::vector<Room> dungeon(50); 
std::vector<Item> items(50);
std::vector<int> inventory(50);

Player *player = new Player();
int currentRoomId = 1; 
bool justEnteredRoom = true;

bool fillItems(std::string fileName){
	std::filebuf fb; 
	if(fb.open(fileName, std::ios::in)){
		std::istream is(&fb); 
			
		//use getline here
		int currentItem = 1; 
		std::string fileLine; 
		while(getline(is, fileLine)){
			std::stringstream ss;
		   	ss << fileLine;	
			std::string token; 
			std::vector<std::string> tokens; 
			
			while(getline(ss, token, '|')){
				tokens.push_back(token); 
			}

			items[currentItem].init(std::stoi(tokens[0]), tokens[1], tokens[2], tokens[3],std::stoi(tokens[4]), 
					std::stoi(tokens[5]), std::stoi(tokens[6]), std::stoi(tokens[7]), std::stoi(tokens[8])); 
			
			currentItem++;
		}	
		fb.close();
	}else{
		return false; 
	}
	return true;
}

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
		
			dungeon[currentRoom].init(tokens[1], std::stoi(tokens[2]), tokens[3], std::stoi(tokens[4]), std::stoi(tokens[5]), std::stoi(tokens[6]), std::stoi(tokens[7])); 

			//insert items into the room
			if(tokens[8].at(0) != ' '){
				std::stringstream isn; 			
				isn << tokens[8];
				while(getline(isn, token, ',')){
					dungeon[currentRoom].addItem(std::stoi(token));
				}
			}
			currentRoom++;
		}	
		fb.close();
	}else{
		return false; 
	}
	return true; 
}

bool grabItem(std::string playerInput){
	if(playerInput.find("grab") != std::string::npos || playerInput.find("take") != std::string::npos || playerInput.find("get") != std::string::npos){
		//get all items in the room
		std::vector<int> roomItemIds = dungeon[currentRoomId].getItemIds();

		//check if an item by any name is in the room
		for(unsigned int i = 0; i < roomItemIds.size(); i++){
				std::cout << items[roomItemIds[i]].getItemName() << std::endl;
				if(playerInput.find(items[roomItemIds[i]].getItemName()) != std::string::npos){
				//print the pickup message
				std::cout << items[roomItemIds[i]].getItemPickupAction() << std::endl;
				//add your item to the inventory
				player->addItem(roomItemIds[i]);
				return true;
			}
		}
		
		std::cout << "Cannot seem to take that." << std::endl;	
		return true;
	}

	return false;
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

bool getInventory(std::string playerInput){

	if(playerInput.find("inventory") != std::string::npos){
		std::cout << player->getName() << " is holding: " << std::endl; 
		for(int itemId : player->getInventory()){
				if(itemId != 0){
					std::cout << items[itemId].getItemName() << std::endl;;	
				}
		}

		return true;
	}


	return false;
}



//Create a large switch statement for different actions when items are used. 
bool useItem(std::string playerInput){
	if(playerInput.find("use") != std::string::npos){

		//check if item referenced is in inventory
		std::vector<int> playerItems = player->getInventory();	
		int foundItemId = -1;
	   	unsigned int itemPlayerIndex = 0;	
		for(; itemPlayerIndex < playerItems.size(); itemPlayerIndex++){
			if(playerInput.find(items[playerItems[itemPlayerIndex]].getItemName()) != std::string::npos && playerItems[itemPlayerIndex] != 0){
					foundItemId = playerItems[itemPlayerIndex];
					break;
			}	
		}
		//check if item was found
		if(foundItemId == -1){
			std::cout << "Item not in inventory" << std::endl;
			return true;
		}

		std::cout << "Found itemID: " << foundItemId << std::endl;

		//item type switch stmt
		if(items[foundItemId].weapon()){
			//check for monster in room, scare if there
			if(dungeon[currentRoomId].monsterInRoom()){
				//check for monster
				std::cout << "You scare the creature off with this menacing swinging of your " << items[foundItemId].getItemName() << "!" << std::endl;
				//take monster out of room	
				dungeon[currentRoomId].removeMonster();	
			}else{
				std::cout << "Nothing to attack with this item!" << std::endl;
			}

		}else if(items[foundItemId].healing()){
			//improve health if hurt!
			if(player->healPlayer()){
				std::cout << "The " << items[foundItemId].getItemName()  << " has healed you to perfect health!" << std::endl;	
			}else{
				std::cout << "You feel a nice zing as you use this item, but it has no real effects." << std::endl;                                                                             
			}
		}else if(items[foundItemId].key()){
			//check room's doors for locked, if locked, open
			if(dungeon[currentRoomId].moveNorth() < 0){
				dungeon[currentRoomId].unlockNorth();
				std::cout << "The northern door has unlocked!" << std::endl;
			}else if(dungeon[currentRoomId].moveSouth() < 0){
				dungeon[currentRoomId].unlockSouth();
				std::cout << "The southern door has unlocked!" << std::endl;
			}else if(dungeon[currentRoomId].moveWest() < 0){
				dungeon[currentRoomId].unlockWest();
				std::cout << "The western door has unlocked!" << std::endl;
			}else if(dungeon[currentRoomId].moveEast() < 0){
				dungeon[currentRoomId].unlockEast();
				std::cout << "The eastern door has unlocked!" << std::endl;
			}
			
		}else if(items[foundItemId].strangeMaterial()){
			//check if player is in room w/ zero door, if so open, else injure/kill!
			std::cout << "The strange object vibrates in your hand" << std::endl;
		}

		return true;
	}	

	return false;
}

bool inspectObject(std::string playerInput){
	if(playerInput.find("inspect") != std::string::npos){
		//check if item referenced is in inventory
		std::vector<int> playerItems = player->getInventory();	
		int foundItemId = -1; 
		for(unsigned int i = 0; i < playerItems.size(); i++){
			if(playerInput.find(items[playerItems[i]].getItemName()) != std::string::npos){
					foundItemId = playerItems[i];
					break;
			}	
		}
		//check if item was found
		if(foundItemId == -1){
			std::cout << "Item not in inventory" << std::endl;
			return true;
		}

		std::cout << items[foundItemId].getItemDescription() << std::endl;

		return true;
	}
	return false;
}

bool searchRoom(std::string playerInput){
	if(playerInput.find("search") != std::string::npos || playerInput.find("look around") != std::string::npos){
			//Describe Room
			std::cout << dungeon[currentRoomId].getRoomDescription() << std::endl;	

			//Describe items in room
			std::cout << "The objects around the room: " << std::endl;	
			std::vector<int> roomItems = dungeon[currentRoomId].getItemIds();
			for(unsigned int i = 0; i < roomItems.size(); i++){
				std::cout << items[roomItems[i]].getItemName() << ": " << items[roomItems[i]].getItemDescription() << std::endl;				
			}

			return true;
	}
	return false;
}

bool processInput(int timesThrough){

	std::string playerInput;
    std::getline(std::cin, playerInput); 

	if(playerInput == "quit" || playerInput == "exit"){
		return false; 
	}

	if(roomMovement(playerInput)){
		return true;
	}
	
	if(getInventory(playerInput)){
		return true;
	}

	if(grabItem(playerInput)){
		return true;
	}

	if(searchRoom(playerInput)){
		return true;
	}	

	if(useItem(playerInput)){
		return true;
	}

	if(timesThrough > 1){
		std::cout << playerInput << " not understood." << std::endl;
	}

	return true;
}

int main(){
	std::cout <<"Please Enter a Name"<<std::endl;
	std::string name;
	std::cin>>name;


	player->init(name, inventory);
	player->setName(name);
	std::cout << "Hello, "<< player->getName() << std::endl;

	if(!fillDungeon("castle.dng")){
		std::cerr << "castle.dng could not be loaded" << std::endl;
		return 1; 
	}	

	if(!fillItems("castle.items")){
		std::cerr << "castle.items could not be loaded" << std::endl;
		return 1;
	}
	
	std::string playerInput; 
	int timesThrough = 0; 
	do{
		if(justEnteredRoom){
			std::cout << dungeon[currentRoomId].getRoomDescription() << " "; 
			if(dungeon[currentRoomId].monsterInRoom()){
				std::cout << dungeon[currentRoomId].getMonsterDescription();
			}
			std::cout << std::endl;
			justEnteredRoom = false; 
		}
		timesThrough++;
	}while(processInput(timesThrough));

	std::cout << "See you next time...!" << std::endl;

	return 0; 
}
