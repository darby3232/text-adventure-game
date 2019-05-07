#include "player.hpp"
#include <vector>
#include <string>
#include <bits/stdc++.h> 


Player::Player(){
}

void Player::setName(std::string name){
	this->playerName = name;
}
std::string Player::getName(){
	return this->playerName;
}
void Player::addItem(int itemId){
	this->inventory.push_back(itemId);
}

bool Player::hurtPlayer(){
	if(isHurt){
		return true;
	}
	
	isHurt = true;
	return false;
}

bool Player::healPlayer(){
	if(isHurt){
		isHurt = false;
		return true;
	}

	return false;
}

std::vector<int> Player::getInventory(){
	return inventory; 
}

void Player::init(std::string playerName, std::vector<int>& inventory){
	this->playerName=playerName;
	this->inventory=inventory;
}
