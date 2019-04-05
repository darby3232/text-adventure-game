#include "room.hpp"

Room::Room(){

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

std::string Room::getRoomDescription(){
	return this->description; 
}

void Room::init(std::string roomDescription, int northRoomId, int southRoomId, int eastRoomId, int westRoomId){

	this->description = roomDescription; 
	this->northRoomId = northRoomId; 
	this->southRoomId = southRoomId; 
	this->eastRoomId = eastRoomId; 
	this->westRoomId = westRoomId; 
}	
