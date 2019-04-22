#include <iostream>
#include <vector>
#include <string>


class Player{

	public:
		Player();
		Player(std::string name);
		void init(std::string playerName, std::vector<std::string> inventory);
		void setName(std::string name);
		void addItem(std::string item); 
		int useItem(std::string item);
		std::string getName(); 
	private:
		std::string playerName;
		std::vector<std::string> inventory;

};
