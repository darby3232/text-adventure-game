#include "room.hpp"

Room::Room(){

}

std::vector<int> Room::getItemIds(){
	return itemIds;
}

void Room::addItem(int itemId){
	itemIds.push_back(itemId);		
}

int Room::moveNorth(){
	return this->northRoomId; 
}

int Room::moveSouth(){
	return this->southRoomId;
}

int Room::moveEast(){
	return this->eastRoomId; 
}

int Room::moveWest(){
	return this->westRoomId;
}

void Room::unlockNorth(){
	northRoomId *= -1; 
}

void Room::unlockSouth(){
	southRoomId *= -1; 
}

void Room::unlockEast(){
	eastRoomId *= -1; 
}

void Room::unlockWest(){
	westRoomId *= -1; 
}

bool Room::monsterInRoom(){
	return hasMonster;
}

void Room::removeMonster(){
	hasMonster = false;
}

std::string Room::getMonsterDescription(){
	return monsterDescription;
}

std::string Room::getRoomDescription(){
	return description;
}

void Room::init(std::string roomDescription, int hasMonster, std::string monsterDescription, int northRoomId, int southRoomId, int eastRoomId, int westRoomId){
	this->hasMonster = hasMonster;
	this->monsterDescription = monsterDescription;
	this->description = roomDescription; 
	this->northRoomId = northRoomId; 
	this->southRoomId = southRoomId; 
	this->eastRoomId = eastRoomId; 
	this->westRoomId = westRoomId; 
}	
