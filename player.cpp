#include "player.hpp"
#include <vector>
#include <string>
#include<bits/stdc++.h> 


Player::Player(){
}

void Player::setName(std::string name){
	this->playerName = name;
}
void Player::addItem(std::string item){
	this->inventory.push_back(item);
}

int Player::useItem(std::string item){

	std::vector<std::string>::iterator it;
	it = std::find(this->inventory.begin(), this->inventory.end(), item);
	if(it !=this->inventory.end())
	{
		this->inventory.erase(it);
		return 1;
	}
	else{
		return 0;
	}
	return 0;
}

void Player::init(std::string playerName, std::vector<std::string> inventory){
	this->playerName=playerName;
	this->inventory=inventory;
}
