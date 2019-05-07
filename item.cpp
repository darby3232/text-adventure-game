#include "item.hpp"

Item::Item(){

}

void Item::init(int itemId, std::string itemName, std::string itemPickupAction, std::string itemDescription, bool isWeapon, bool isHealing, bool isKey, bool isStrangeMaterial, int uses){
	this -> itemId = itemId;
	this -> itemName = itemName; 
	this -> itemPickupAction = itemPickupAction;
	this -> itemDescription = itemDescription; 
	this -> isWeapon = isWeapon;
	this -> isHealing = isHealing; 
	this -> isKey = isKey;
	this -> isStrangeMaterial = isStrangeMaterial;
	this -> uses = uses;
}

std::string Item::getItemPickupAction(){
	return itemPickupAction;
}

std::string Item::getItemName(){
	return itemName;
}

std::string Item::getItemDescription(){
	return itemDescription;
}

bool Item::weapon(){
	return isWeapon;
}

bool Item::healing(){
	return isHealing;
}

bool Item::key(){
	return isKey;
}

bool Item::strangeMaterial(){
	return isStrangeMaterial;
}

int Item::getUses(){
	return uses;
}
